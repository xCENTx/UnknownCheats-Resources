#pragma once

//  FOR d3d matrix
#include <d3d9.h>   //  
#include <d3dx9.h>  //  D3DMatrix
#include <vector>   //  bone maps

namespace UnrealEngine
{
    /// 
    ///     FLAGS
    ///  

    enum class EObjectFlags : __int32
    {
        NoFlags = 0x00000000,

        Public = 0x00000001,
        Standalone = 0x00000002,
        MarkAsNative = 0x00000004,
        Transactional = 0x00000008,
        ClassDefaultObject = 0x00000010,
        ArchetypeObject = 0x00000020,
        Transient = 0x00000040,

        MarkAsRootSet = 0x00000080,
        TagGarbageTemp = 0x00000100,

        NeedInitialization = 0x00000200,
        NeedLoad = 0x00000400,
        KeepForCooker = 0x00000800,
        NeedPostLoad = 0x00001000,
        NeedPostLoadSubobjects = 0x00002000,
        NewerVersionExists = 0x00004000,
        BeginDestroyed = 0x00008000,
        FinishDestroyed = 0x00010000,

        BeingRegenerated = 0x00020000,
        DefaultSubObject = 0x00040000,
        WasLoaded = 0x00080000,
        TextExportTransient = 0x00100000,
        LoadCompleted = 0x00200000,
        InheritableComponentTemplate = 0x00400000,
        DuplicateTransient = 0x00800000,
        StrongRefOnFrame = 0x01000000,
        NonPIEDuplicateTransient = 0x02000000,
        Dynamic = 0x04000000,
        WillBeLoaded = 0x08000000,
    };


    /// 
    ///     STRUCTS
    ///  

    struct FName
    {
        __int32 ComparisonIndex;	//0x0000
        __int32 Number;	//0x0004
    };

    template <class T>
    struct TArray
    {
        T data;	    //0x0000
        __int32 count;	//0x0008
        __int32 max;	//0x000C
    };	//Size: 0x0010

    struct FVector2D
    {
        float X, Y;


        FVector2D()
        {
            X = 0;
            Y = 0;
        }

        FVector2D(float x, float y)
        {
            X = x;
            Y = y;
        }

        FVector2D operator+(const FVector2D& other) const { return FVector2D{ X + other.X, Y + other.Y }; }

        FVector2D operator-(const FVector2D& other) const { return FVector2D{ X - other.X, Y - other.Y }; }

        FVector2D operator*(float scalar) const { return FVector2D{ X * scalar, Y * scalar }; }

        FVector2D operator/(float scalar) const { return FVector2D{ X / scalar, Y / scalar }; }

        FVector2D operator=(float* other) const { return FVector2D{ other[0], other[1] }; }

        FVector2D& operator*=(const FVector2D& other)
        {
            X += other.X;
            Y += other.Y;
            return *this;
        }


        bool IsValid() { return X == 0 && Y == 0; }

        float Distance(const FVector2D& other) const;
    };

    struct FVector
    {
        float X;	//0x0000
        float Y;	//0x0008
        float Z;	//0x0010

        FVector()
        {
            X = 0;
            Y = 0;
            Z = 0;
        }

        FVector(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        FVector operator+(const FVector& other) const { return FVector{ X + other.X, Y + other.Y, Z + other.Z }; }

        FVector operator-(const FVector& other) const { return FVector{ X - other.X, Y - other.Y, Z - other.Z }; }

        FVector operator*(float scalar) const { return FVector{ X * scalar, Y * scalar, Z * scalar }; }

        FVector operator/(float scalar) const { return FVector{ X / scalar, Y / scalar, Z / scalar }; }

        FVector operator=(float* other) const { return FVector{ other[0], other[1], other[2] }; }

        FVector& operator+=(const FVector& other)
        {
            X += other.X;
            Y += other.Y;
            Z += other.Z;
            return *this;
        }

        FVector& operator*=(const FVector& other)
        {
            X *= other.X;
            Y *= other.Y;
            Z *= other.Z;
            return *this;
        }

        FVector& operator*=(const float scalar) {
            X *= scalar;
            Y *= scalar;
            Z *= scalar;
            return *this;
        }

        bool IsValid();
        float Dot(FVector& other);
        float Distance(FVector& other);
    };	//Size: 0x0018

    struct FRotator
    {
        float Pitch;	//0x0000
        float Yaw; 	//0x0008
        float Roll;	//0x0010

        FVector ToVector();
        void GetAxes(FVector* Xaxis, FVector* Yaxis, FVector* Zaxis);
    };	//Size: 0x0018

    struct FQuat
    {
        float X;	//0x0000
        float Y;	//0x0008
        float Z;	//0x0010
        float W;	//0x0018

    };	//Size: 0x0020

    struct FTransform
    {
        FQuat Rotation;	//0x0000
        FVector Translation;	//0x0010
        char pad_001C[4];	//0x001C
        FVector Scale3D;	//0x0020
        char pad_002C[4];	//0x002C

        //  copy pasta
        D3DMATRIX to_matrix_with_scale();
    };	//Size: 0x0060

    struct FMatrix4x4
    {
        float m[4][4];

        //  
        FMatrix4x4();
        FMatrix4x4(const D3DMATRIX& MX);
        FMatrix4x4(const FTransform& TM);
        FMatrix4x4(const FRotator& rot, const FVector& origin = FVector(0, 0, 0));

        //  
        FMatrix4x4 operator*(const FMatrix4x4& other) const;

        //  
        FVector GetLocation() const;
    };  //Size: 0x0040

    struct FString
    {
        __int64 data;   //  const wchar_t*
        __int32 count;
        __int32 max;
    };

    struct FMinimalViewInfo
    {
        FVector Location;	//0x0000
        FRotator Rotation;	//0x0018
        float Fov;	//0x0030	
        char pad_001C[1492];	//0x001C
    };	//Size: 0x05F0

    struct FCameraCacheEntry
    {
        float Timestamp;	//0x0000
        char pad_0004[12];	//0x0004
        FMinimalViewInfo POV;	//0x0010
    };	//Size: 0x0600

    struct FGameplayAttributeData
    {
        unsigned char Pad_0[0x8];           // 0x0000
        float BaseValue;                    // 0x0008
        float CurrentValue;                 // 0x000C
    };

    namespace Classes
    {
        struct UObject
        {
            char pad_0000[8];	//0x0000    ;   VFTable
            int UFlags;	        //0x0008
            int UIndex;	        //0x000C
            __int64 UClass;	    //0x0010    ;   UClass*
            FName UName;	    //0x0018
            __int64 Outer;	    //0x0020    ;   UObject*
        };	//Size: 0x0028

        struct UField
        {
            UObject UObject;	//0x0000
            __int64 Next;	//0x0028                ;   UField*
        };	//Size: 0x0030

        struct UStruct
        {
            UField UField;	//0x0000
            char   Pad_30[16];       // 0x0030
            __int64 Super;           // 0x0040;   UStruct*
            __int64 Children;        // 0x0048;   UField*
            __int64 ChildProperties; // 0x0050;   UField*
            __int32   Size;          // 0x0058
            __int32   MinAlignemnt;  // 0x005C
            char   Pad_60[80];       // 0x0060
        };	//Size: 0x00B0

        struct UClass
        {
            UStruct UStruct;	//0x0000
            //  char                                         Pad_B0[32];   
            //  enum class EClassCastFlags                    CastFlags;   
            char Pad_B0[40];                                    
            char Pad_D8[64];                                    
            __int64 DefaultObject;                              
            char Pad_120[272];                                  
        };	//Size: 0x0230

        struct FNameEntryAllocator
        {
            __int64 frwLock;	//0x0000
            int CurrentBlock;	//0x0008
            int CurrentByteCursor;	//0x000C
            __int64 Blocks[8192];	//0x0010    ;   BlockData*
        };	//Size: 0x10010

        struct TUObject
        {
            __int64 pObject;	//0x0000
            char pad_0008[16];	//0x0008
        };	//Size: 0x0018

        struct UObjectPool
        {
            __int64 ObjectArray;	//0x0000    ;   TUObject*
            char pad_0008[12];	//0x0008
            int ObjectCount;	//0x0014
        };	//Size: 0x0018

        struct FNamePool
        {
            FNameEntryAllocator FNameEntryAllocator;	//0x0000
            int AnsiCount;	//0x10010
            int WideCount;	//0x10014
        };	//Size: 0x10018

        struct BlockData
        {
            char pad_0000[136];	//0x0000
        };	//Size: 0x0088

        struct UAttributeSet
        {
            UObject UObject;
            char pad_0028[8];   // 0x0028(0x0008)
        };

        struct UWorld
        {
            UObject UObject;	//0x0000
            char pad_0028[8];	//0x0028
            __int64 PersistentLevel;	//0x0030
            char pad_0038[224];	//0x0038
            __int64 GameMode;	//0x0118
            __int64 GameState;	//0x0120
            char pad_0128[88];	//0x0128
            __int64 OwningGameInstance;	//0x0180
        };	//Size: 0x0188

        struct UActorComponent
        {
            UObject UObject;	//0x0000
            char pad_0028[136];	//0x0028
        };	//Size: 0x00B0

        struct USceneComponent
        {
            UActorComponent UActorComponent;	//0x0000	
            char pad_00B0[108];	//0x00B0
            FVector RelativeLocation;	//0x011C
            FRotator RelativeRotation;	//0x0128
            FVector RelativeScale3D;	//0x0134
            FVector ComponentVelocity;	//0x0140
            char pad_014C[116];	//0x014C
            FTransform ComponentToWorld;	//0x01C0
            char pad_01F0[8];	//0x01F0
        };	//Size: 0x01F8

        struct UPrimitiveComponent
        {
            USceneComponent USceneComponent;	//0x0000	
            char pad_01F8[600];	//0x01F8
        };	//Size: 0x0450

        struct UMeshComponent
        {
            UPrimitiveComponent UPrimitiveComponent;	//0x0000
            char pad_0450[48];	//0x0450
        };	//Size: 0x0480

        struct USkinnedMeshComponent
        {
            UMeshComponent UMeshComponent;	//0x0000
            char pad_0480[48];	//0x0480
            TArray<__int64> BoneArray;	//0x04B0
            char pad_04C0[480];	//0x04C0
        };	//Size: 0x06A0

        struct USkeletalMeshComponent
        {
            USkinnedMeshComponent USkinnedMeshComponent;	//0x0000
            char pad_06A0[8];	//0x06A0
        };	//Size: 0x06A8

        struct AActor
        {
            UObject UObject;	//0x0000
            char pad_0028[272];	//0x0028
            __int64 RootComponent;	//0x0138
            char pad_0140[232];	//0x0140
        };	//Size: 0x0228

        struct AController
        {
            AActor AActor;	                //0x0000
            char pad_0228[8];	//0x0228
            __int64 PlayerState;	//0x0230
            char pad_0238[32];	//0x0238
            __int64 Pawn;	//0x0258
            char pad_0260[8];	//0x0260
            __int64 Character;	//0x0268
            char pad_0270[48];	//0x0270
        };  //  0x02A0

        struct APlayerController
        {
            AController AController;	    //0x0000
            __int64 Player;	//0x02A0
            __int64 AcknowledgedPawn;	//0x02A8
            char pad_02B0[16];	//0x02B0
            __int64 PlayerCameraManager;	//0x02C0
            char pad_02C8[688];	//0x02C8
        };	//Size: 0x0578

        struct AInfo
        {
            AActor AActor;	//0x0000
        };	//Size: 0x02A0

        struct APlayerState
        {
            AInfo AInfo;	                //0x0000
            char pad_0228[96];	//0x0228
            __int64 PawnPrivate;	//0x0288
            char pad_0290[120];	//0x0290
            FString PlayerNamePrivate;	//0x0308
            char pad_0318[24];	//0x0318
        };	//Size: 0x0330

        struct APawn
        {
            AActor AActor;	                //0x0000
            char pad_0228[32];	//0x0228
            __int64 PlayerState;	//0x0248
            char pad_0250[16];	//0x0250
            __int64 Controller;	//0x0260
            char pad_0268[32];	//0x0268
        };	//Size: 0x0288

        struct ACharacter
        {
            APawn APawn;	                //0x0000
            __int64 Mesh;	//0x0288
            char pad_0290[552];	//0x0290
        };	//Size: 0x04B8
    };

    namespace Offsets
    {
        constexpr auto GObjects = 0x7217040;    
        constexpr auto GNames = 0x71DAAC0;      
        constexpr auto GWorld = 0x735B820;

        namespace World
        {
            constexpr auto PersistentLevel = 0x30;      //  ULevel
            constexpr auto AuthorityGameMode = 0x0118;  //  AGameMode
            constexpr auto GameState = 0x0120;          //  AGameState
            constexpr auto Levels = 0x138;              //  TArray<ULevel*>
            constexpr auto OwningGameInstance = 0x0180; //  UGameInstance
        }

        namespace Level
        {
            constexpr auto Actors = 0x98;   //  TArray<AActor*>
        }

        namespace GameMode
        {
            constexpr auto GameState = 0x300;
        }

        namespace GameState
        {
            constexpr auto AuthorityGameMode = 0x02A8;    //  AGameModeBAse
            constexpr auto PlayerArray = 0x0240;    // TArray<APlayerState*>
        }

        namespace GameInstance
        {
            constexpr auto LocalPlayers = 0x0038;    //  TArray<ULocalPlayer*>
        }

        namespace UPlayer
        {
            constexpr auto PlayerController = 0x0030;    //  APlayerController
            constexpr auto ViewportClient = 0x0070;    //  UGameViewportClient
        }

        namespace Actor
        {
            constexpr auto RootComponent = 0x0138; //  USceneComponent
        }

        namespace Controller
        {
            using namespace Actor;

            constexpr auto PlayerState = 0x0230;    //  APlayerState
            constexpr auto Pawn = 0x0258;    //  APawn
            constexpr auto Character = 0x0268;    //  ACharacter
            constexpr auto Player = 0x02A0;    //  UPlayer
            constexpr auto AcknowledgedPawn = 0x02A8;    //  APawn
            constexpr auto PlayerCameraManager = 0x02C0;    //  APlayerCameraManager
        }

        namespace Pawn
        {
            using namespace Actor;

            constexpr auto PlayerState = 0x0248;    //  APlayerState
            constexpr auto Controller = 0x0260;    //  AController
            constexpr auto Name = 0x368;            //   FString
        }

        namespace PlayerState
        {
            constexpr auto PawnPrivate = 0x0288;    //  APawn
            constexpr auto PlayerNamePrivate = 0x0308;    //  FString
        }

        namespace Character
        {
            using namespace Pawn;

            constexpr auto Mesh = 0x0288;    //  USkeletalMeshComponent
        }

        namespace APlayerCameraManager
        {
            constexpr auto PCOwner = 0x0228;    //  APlayerController
            constexpr auto TransformComponent = 0x0230;    //  USceneComponent
            constexpr auto CameraCachePrivate = 0x1AF0;    //  FCameraCacheEntry
        }

        namespace USceneComponent
        {
            constexpr auto RelativeLocation = 0x011C;    //  FVector
            constexpr auto RelativeRotation = 0x0128;    //  FRotator
            constexpr auto RelativeScale3D = 0x0134;    //  FVector
            constexpr auto ComponentVelocity = 0x0140;    //  FVector
        }

        namespace USkeletalMeshComponent
        {
            constexpr auto RenderTime = 0x300; // FVector   //  BoundsScale = 0x2EC
            constexpr auto ComponentToWorld = 0x01C0;    //  FTransform
            constexpr auto BoneArray = 0x04B0;    //  TArray<FTransform>
        }
    }

    namespace Tools
    {
        bool IsValidPosition(FVector pos);
        FVector GetLookDir(FRotator rotation);
        FVector GetUpDir(FRotator rotation);
        FVector GetRightDir(FRotator rotation);
        void RotatePoint(const FVector point, const FVector& center, const FQuat angles, FVector* result);
        bool TransformWorldToScreen(FCameraCacheEntry CameraView, FVector WorldLocation, FVector2D& Screen2D, FVector2D cxSize, bool isRelative);

        //  copy pasta
        D3DMATRIX to_matrix(FRotator rot, FVector origin = FVector(0, 0, 0));
        D3DMATRIX matrix_multiplication(D3DMATRIX pm1, D3DMATRIX pm2);
    }


    /// 
    ///     EXTRAS
    ///  

    struct CameraView
    {
        FVector location;
        FRotator rotation;
        float fov;
    };

    struct EntityTransform
    {
        FVector pos;
        FRotator rot;
        FVector scale;
        FVector velocity;
    };

    struct AABB
    {
        FVector m_min;
        FVector m_max;

        AABB()
        {
            m_min = FVector();
            m_max = FVector();
        }

        AABB(FVector min, FVector max)
        {
            m_min = min;
            m_max = max;
        }

        FVector Center() const { return (m_min + m_max) * 0.5f; }
        FVector Size() const { return m_max - m_min; }  //  width, height, depth
        FVector Extents() const { return Size() * 0.5f; }
        FVector* Vertices()
        {
            UnrealEngine::FVector verts[] =
            {
                UnrealEngine::FVector(m_min.X, m_min.Y, m_min.Z),
                UnrealEngine::FVector(m_max.X, m_min.Y, m_min.Z),
                UnrealEngine::FVector(m_max.X, m_min.Y, m_max.Z),
                UnrealEngine::FVector(m_min.X, m_min.Y, m_max.Z),
                UnrealEngine::FVector(m_min.X, m_max.Y, m_min.Z),
                UnrealEngine::FVector(m_max.X, m_max.Y, m_min.Z),
                UnrealEngine::FVector(m_max.X, m_max.Y, m_max.Z),
                UnrealEngine::FVector(m_min.X, m_max.Y, m_max.Z),
            };

            return verts;
        }
    };
}


namespace SquadGame
{
    enum Bones : __int32
    {
        Root = 0,
        Bip01 = 1,
        Pelvis = 2,
        Spine = 3,
        Spine1 = 4,
        Spine2 = 5,
        Neck = 6,
        Head = 7,
        HeadNub = 8,
        REye = 9,
        REyeNub = 10,
        LEye = 11,
        LEyeNub = 12,
        MJaw = 13,
        MJawNub = 14,
        MBottomLip = 15,
        MBottomLipNub = 16,
        MTongue = 17,
        MTongueNub = 18,
        LMouthBottom = 19,
        LMouthBottomNub = 20,
        RMouthBottom = 21,
        RMouthBottomNub = 22,
        RMasseter = 23,
        RMasseterNub = 24,
        LMasseter = 25,
        LMasseterNub = 26,
        MUpperLip = 27,
        MUpperLipNub = 28,
        RCaninus = 29,
        RCaninusNub = 30,
        LCaninus = 31,
        LCaninusNub = 32,
        REyeBlinkBottom = 33,
        REyeBlinkBottomNub = 34,
        LEyeBlinkBottom = 35,
        LEyeBlinkBottomNub = 36,
        RUpperlip = 37,
        RUpperlipNub = 38,
        LUpperlip = 39,
        LUpperlipNub = 40,
        RMouthCorner = 41,
        RMouthCornerNub = 42,
        LMouthCorner = 43,
        LMouthCornerNub = 44,
        RCheek = 45,
        RCheekNub = 46,
        LCheek = 47,
        LCheekNub = 48,
        REyeBlinkTop = 49,
        REyeBlinkTopNub = 50,
        LEyeBlinkTop = 51,
        LEyeBlinkTopNub = 52,
        RInnerEyebrow = 53,
        RInnerEyebrowNub = 54,
        LInnerEyebrow = 55,
        LInnerEyebrowNub = 56,
        MMiddleEyebrow = 57,
        MMiddleEyebrowNub = 58,
        ROuterEyebrow = 59,
        ROuterEyebrowNub = 60,
        LOuterEyebrow = 61,
        LOuterEyebrowNub = 62,
        MNose = 63,
        MNoseNub = 64,
        R_Clavicle = 65,
        R_UpperArm = 66,
        R_Forearm = 67,
        R_Hand = 68,
        R_Finger0 = 69,
        R_Finger01 = 70,
        R_Finger02 = 71,
        R_Finger0Nub = 72,
        R_Finger1 = 73,
        R_Finger11 = 74,
        R_Finger12 = 75,
        R_Finger1Nub = 76,
        R_Finger2 = 77,
        R_Finger21 = 78,
        R_Finger22 = 79,
        R_Finger2Nub = 80,
        R_Finger3 = 81,
        R_Finger31 = 82,
        R_Finger32 = 83,
        R_Finger3Nub = 84,
        R_Finger4 = 85,
        R_Finger41 = 86,
        R_Finger42 = 87,
        R_Finger4Nub = 88,
        R_ForeTwist = 89,
        R_ForeTwist1 = 90,
        R_ForeTwist2 = 91,
        L_Clavicle = 92,
        L_UpperArm = 93,
        L_Forearm = 94,
        L_Hand = 95,
        L_Finger0 = 96,
        L_Finger01 = 97,
        L_Finger02 = 98,
        L_Finger0Nub = 99,
        L_Finger1 = 100,
        L_Finger11 = 101,
        L_Finger12 = 102,
        L_Finger1Nub = 103,
        L_Finger2 = 104,
        L_Finger21 = 105,
        L_Finger22 = 106,
        L_Finger2Nub = 107,
        L_Finger3 = 108,
        L_Finger31 = 109,
        L_Finger32 = 110,
        L_Finger3Nub = 111,
        L_Finger4 = 112,
        L_Finger41 = 113,
        L_Finger42 = 114,
        L_Finger4Nub = 115,
        L_ForeTwist = 116,
        L_ForeTwist1 = 117,
        L_ForeTwist2 = 118,
        IK_Weapon_Root = 119,
        IK_Weapon = 120,
        CameraBone = 121,
        Weapon1 = 122,
        IK_Weapon_L_Hand = 123,
        IK_Weapon_R_Hand = 124,
        L_Thigh = 125,
        L_Calf = 126,
        L_Foot = 127,
        L_Toe0 = 128,
        L_Toe0Nub = 129,
        R_Thigh = 130,
        R_Calf = 131,
        R_Foot = 132,
        R_Toe0 = 133,
        R_Toe0Nub = 134,
        IK_Hand_Root = 135,
        IK_L_Hand = 136,
        IK_R_Hand = 137,
        IK_Feet_Root = 138,
        IK_Left_Foot = 139,
        IK_Right_Foot = 140
    };

    static std::vector<std::vector<int>> BoneVector
    {
        { Bones::L_Hand, Bones::L_Forearm, Bones::L_UpperArm, Bones::Neck },            // Left hand -> neck
        { Bones::R_Hand, Bones::R_Forearm, Bones::R_UpperArm, Bones::Neck },            // Right hand -> neck
        { Bones::L_Toe0, Bones::L_Foot, Bones::L_Calf, Bones::L_Thigh, Bones::Spine },   // Left foot -> bottom spine
        { Bones::R_Toe0, Bones::R_Foot, Bones::R_Calf, Bones::R_Thigh, Bones::Spine },   // Right foot -> bottom spine
        { Bones::Spine, Bones::Spine2, Bones::Neck, Bones::Head }                   // Bottom spine -> head
    };

    static std::vector<std::vector<int>> BoneHandsLVector
    {
        // 
        { Bones::L_Hand, Bones::L_Finger0, Bones::L_Finger01, Bones::L_Finger02, Bones::L_Finger0Nub },          //  Thumb
        { Bones::L_Hand, Bones::L_Finger1, Bones::L_Finger11, Bones::L_Finger12, Bones::L_Finger1Nub },          //  Index
        { Bones::L_Hand, Bones::L_Finger2, Bones::L_Finger21, Bones::L_Finger22, Bones::L_Finger2Nub },      //  Middle
        { Bones::L_Hand, Bones::L_Finger3, Bones::L_Finger31, Bones::L_Finger32, Bones::L_Finger3Nub },              //  Ring
        { Bones::L_Hand, Bones::L_Finger4, Bones::L_Finger41, Bones::L_Finger42, Bones::L_Finger4Nub },          //  Pinky
    };

    static std::vector<std::vector<int>> BoneHandsRVector
    {
        // 
        { Bones::R_Hand, Bones::R_Finger0, Bones::R_Finger01, Bones::R_Finger02, Bones::R_Finger0Nub },          //  Thumb
        { Bones::R_Hand, Bones::R_Finger1, Bones::R_Finger11, Bones::R_Finger12, Bones::R_Finger1Nub },          //  Index
        { Bones::R_Hand, Bones::R_Finger2, Bones::R_Finger21, Bones::R_Finger22, Bones::R_Finger2Nub },      //  Middle
        { Bones::R_Hand, Bones::R_Finger3, Bones::R_Finger31, Bones::R_Finger32, Bones::R_Finger3Nub },              //  Ring
        { Bones::R_Hand, Bones::R_Finger4, Bones::R_Finger41, Bones::R_Finger42, Bones::R_Finger4Nub },          //  Pinky
    };
    
    static std::vector<int> BoneAimVector
    {
        Bones::Spine2, Bones::Neck, Bones::Head
    };

    namespace Offsets
    {
        using namespace UnrealEngine::Offsets;

        namespace AGzPlayerState
        {
            using namespace PlayerState;

            constexpr auto Team = 0x0400;       //  __int32
            constexpr auto Soldier = 0x0768;  //  ASQSoldier*
        }

        namespace AGzCharacter
        {
            using namespace Character;

            constexpr auto WeaponBasedFOV = 0x05A8;    //  float
            constexpr auto GunOffset = 0x1634;  //  FVector
            constexpr auto Health = 0x1DF8;  //  float
        }
    }

    namespace Classes
    {
        using namespace UnrealEngine::Classes;

        //  ASQPlayerController > APlayerController > AController > AActor > UObject
        struct ASQPlayerController
        {
            APlayerController APlayerController;	        //0x0000

        };  //Size: 

        //  ASQPlayerState > APlayerState > AInfo > AActor > UObject
        struct ASQPlayerState
        {
            APlayerState APlayerState;	                    //0x0000	
            char pad_0330[208];	//0x0330
            int TeamID;	//0x0400
            char pad_0404[868];	//0x0404
            __int64 Soldier;	//0x0768
            char pad_0770[240];	//0x0770

        };	//Size: 0x0860

        //  ASQSoldier > ACharacter > APawn > AActor > UObject
        struct ASQSoldier
        {
            ACharacter ACharacter;	                        //0x0000
            char pad_04B8[240];	//0x04B8
            float WeaponBasedFOV;	//0x05A8
            char pad_05AC[4232];	//0x05AC
            UnrealEngine::FVector GunOffset;	//0x1634
            char pad_1640[1976];	//0x1640
            float Health;	//0x1DF8
            char pad_1DFC[2148];	//0x1DFC
        };  //Size: 0x2660
    }
}