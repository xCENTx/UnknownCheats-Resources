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
        int ComparisonIndex;	//0x0000
        int Number;	//0x0004
    };

    template <class T>
    struct TArray
    {
        T data;	    //0x0000
        int count;	//0x0008
        int max;	//0x000C
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

        //  FVector2D operator=(const Vector2 other) const { return FVector2D{ other.x, other.y }; }

        //  FVector2D operator=(const ImVec2 other) const { return FVector2D{ other.x, other.y }; }

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
        double X;	//0x0000
        double Y;	//0x0008
        double Z;	//0x0010


        FVector()
        {
            X = 0;
            Y = 0;
            Z = 0;
        }

        FVector(double x, double y, double z)
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
        double Pitch;	//0x0000
        double Yaw; 	//0x0008
        double Roll;	//0x0010

        FVector ToVector();
        void GetAxes(FVector* Xaxis, FVector* Yaxis, FVector* Zaxis);
    };	//Size: 0x0018

    struct FQuat
    {
        double X;	//0x0000
        double Y;	//0x0008
        double Z;	//0x0010
        double W;	//0x0018

    };	//Size: 0x0020

    struct FTransform
    {
        FQuat Rotation;	//0x0000
        FVector Translation;	//0x0020
        char pad_0038[8];	//0x0038
        FVector Scale3D;	//0x0040
        char pad_0058[8];	//0x0058

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
        int count;
        int max;
    };

    struct FMinimalViewInfo
    {
        FVector Location;	//0x0000
        FRotator Rotation;	//0x0018
        float Fov;	//0x0030
        float DesiredFOV;	//0x0034
        float OrthoWidth;	//0x0038
        float OrthoNearClipPlane;	//0x003C
        float OrthoFarClipPlane;	//0x0040
        float PerspectiveNearClipPlane;	//0x0044
        float AspectRatio;	//0x0048
    };	//Size: 0x07C0

    struct FCameraCacheEntry
    {
        float Timestamp;	//0x0000
        char pad_0004[12];	//0x0004
        FMinimalViewInfo POV;	//0x0010
    };	//Size: 0x07D0

    struct FGameplayAttributeData
    {
        unsigned char Pad_0[0x8];           // 0x0000
        float BaseValue;                    // 0x0008
        float CurrentValue;                 // 0x000C
    };

    //  custom struct
    struct CameraView
    {
        FVector location;
        FRotator rotation;
        float fov;
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
            char pad_0030[16];	//0x0030
            __int64 Super;	//0x0040                ;   UStruct*
            __int64 Children;	//0x0048            ;   UField*
            __int64 ChildrenProperties;	//0x0050    ;   UField*
            int Size;	//0x0058
            int MinAlignment;	//0x005C
            char pad_0060[80];	//0x0060
        };	//Size: 0x00B0

        struct UClass
        {
            UStruct UStruct;	//0x0000
            char pad_00B0[96];	//0x00B0
            __int64 DefaultObject;	//0x0110        ;   UObject*
            char pad_0118[232];	//0x0118
        };	//Size: 0x0200

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
            char pad_0028[8];   // 0x0028(0x0008)(Fixing Struct Size After Last Property [ Dumper-7 ])
        };

        struct UWorld
        {
            UObject UObject;	//0x0000
            char pad_0028[8];	//0x0028
            __int64 PersistentLevel;	//0x0030
            char pad_0038[296];	//0x0038
            __int64 GameState;	//0x0160
            char pad_0168[16]; // 0x0168
            //  char pad_0168[112];	//0x0168    -> without levels
            TArray<__int64> Levels; //0x0178
            char pad_0188[80];	//0x0188
            __int64 OwningGameInstance;	//0x01D8
        };	//Size: 0x01E0

        struct UActorComponent
        {
            UObject UObject;	//0x0000
            char pad_0028[128];	//0x0028
        };	//Size: 0x00A8

        struct USceneComponent
        {
            UActorComponent UActorComponent;	//0x0000
            char pad_00A8[136];	//0x00A8
            FVector RelativeLocation;	//0x0130
            FRotator RelativeRotation;	//0x0148
            FVector RelativeScale3D;	//0x0160
            FVector ComponentVelocity;	//0x0178
            char pad_0190[64];	//0x0190
            FTransform ComponentToWorld;	//0x01D0
        };	//Size: 0x0230

        struct UPrimitiveComponent
        {
            USceneComponent USceneComponent;	//0x0000
            //  char pad_0230[752];	//0x0230	
            //  char pad_0230[208];	//0x0230 -> LastSubmitTime
            char pad_0230[188];	//0x0230    -> BoundsScale
            float BoundsScale;  //0x02EC
            char pad_02F0[16];   //0x2F0
            float LastSubmitTime;	//0x0300
            float LastRenderTime;	//0x0304
            float LastRenderTime2;	//0x0308
            char pad_030C[532];	//0x030C

        };	//Size: 0x0520

        struct UMeshComponent
        {
            UPrimitiveComponent UPrimitiveComponent;	//0x0000
            char pad_0520[48];	//0x0520
        };	//Size: 0x0550

        struct USkinnedMeshComponent
        {
            UMeshComponent UMeshComponent;	//0x0000
            char pad_0558[128];	//0x0550
            TArray<__int64> BoneArray;	//0x05D0
            char pad_05E0[736];	//0x05E0
        };	//Size: 0x08C0

        struct USkeletalMeshComponent
        {
            USkinnedMeshComponent USkinnedMeshComponent;	//0x0000
            char pad_08C0[1712];	//0x08C0
        };	//Size: 0x0F70

        struct AActor
        {
            UObject UObject;	//0x0000
            char pad_0028[384];	//0x0028
            __int64 RootComponent;	//0x01A8
            char pad_01B0[232];	//0x01B0
        };	//Size: 0x0298

        struct AController
        {
            AActor AActor;	                //0x0000
            char pad_02A0[8];	            //0x0298
            __int64 PlayerState;	        //0x02A0        //  APlayerState*
            char pad_02A8[48];	            //0x02A8
            __int64 Pawn;	                //0x02D8        //  APawn*
            char pad_02E0[8];	            //0x02E0        
            __int64 Character;	            //0x02E8        //  ACharacter*
            __int64 TransformComponent;	    //0x02F0        //  USceneComponent*
            char pad_02F8[24];	            //0x02F8
            FRotator ControlRotation;       //0x0310
            char pad_0328[8];               //0x0328
        };  //  0x0330

        struct APlayerController
        {
            AController AController;	    //0x0000
            char pad_0330[8];	            //0x0330
            __int64 Player;	                //0x0338        //  UPlayer*
            __int64 AcknowledgedPawn;	    //0x0340        //  APawn*
            char pad_0348[8];	            //0x0348        //  AHUD*      
            __int64 PlayerCameraManager;	//0x0350        //  APlayerCameraManager*
            char pad_0358[1288];	        //0x0358
        };	//Size: 0x0888

        struct AInfo
        {
            AActor AActor;	//0x0000
        };	//Size: 0x02A0

        struct APlayerState
        {
            AInfo AInfo;	                //0x0000
            char pad_0298[120];	            //0x0298
            __int64 PawnPrivate;	        //0x0310	
            char pad_0318[56];	            //0x0318
        };	//Size: 0x0350

        struct APawn
        {
            AActor AActor;	                //0x0000
            char pad_0298[32];	            //0x0298
            __int64 PlayerState;	        //0x02B8
            char pad_02C0[16];	            //0x02C0
            __int64 Controller;	            //0x02D0
            char pad_02D8[72];	            //0x02D8
        };	//Size: 0x0320

        struct ACharacter
        {
            APawn APawn;	                //0x0000
            __int64 Mesh;	                //0x0320
            __int64 CharacterMovement;	    //0x0328
            char pad_0338[848];	            //0x0330
        };	//Size: 0x0680
    };

    namespace Offsets
    {
        /// 0.2.0.4
        constexpr auto GObjects = 0x09A5C1C0;    //  
        constexpr auto GNames = 0x099A4F00;      //  
        constexpr auto GWorld = 0x09BDF6F8;      // 

        namespace World
        {
            constexpr auto PersistentLevel = 0x30;      //  ULevel
            constexpr auto AuthorityGameMode = 0x0158;  //  AGameMode
            constexpr auto GameState = 0x0160;          //  AGameState
            constexpr auto Levels = 0x178;              //  TArray<ULevel*>
            constexpr auto OwningGameInstance = 0x01D8; //  UGameInstance
        }

        namespace Level
        {
            constexpr auto Actors = 0xA0;   //  TArray<AActor*>
        }

        namespace GameMode
        {
            constexpr auto GameState = 0x2F8;
        }

        namespace GameState
        {
            constexpr auto AuthorityGameMode = 0x02A0;    //  AGameModeBAse
            constexpr auto PlayerArray = 0x02B0;    // TArray<APlayerState*>
        }

        namespace GameInstance
        {
            constexpr auto LocalPlayers = 0x0038;    //  TArray<ULocalPlayer*>
        }

        namespace UPlayer
        {
            constexpr auto PlayerController = 0x0030;    //  APlayerController
            constexpr auto ViewportClient = 0x0078;    //  UGameViewportClient
        }

        namespace Actor
        {
            constexpr auto Instigator = 0x0190; //  APawn
            constexpr auto RootComponent = 0x01A8; //  USceneComponent
        }

        namespace Controller
        {
            using namespace Actor;

            constexpr auto PlayerState = 0x02A0;            //  APlayerState
            constexpr auto Pawn = 0x02D8;                   //  APawn
            constexpr auto Character = 0x02E8;              //  ACharacter
            constexpr auto TransformComponent = 0x02F0;     //  USceneComponent
            constexpr auto Player = 0x0338;                 //  UPlayer
            constexpr auto AcknowledgedPawn = 0x0340;       //  APawn
            constexpr auto PlayerCameraManager = 0x0350;    //  APlayerCameraManager
        }

        namespace Pawn
        {
            using namespace Actor;

            constexpr auto PlayerState = 0x02B8;    //  APlayerState
            constexpr auto Controller = 0x02D0;     //  AController
            constexpr auto Name = 0x360;            //   FString
        }

        namespace PlayerState
        {
            constexpr auto PawnPrivate = 0x0310;    //  APawn
            constexpr auto PlayerNamePrivate = 0x0360;    //  FString
        }

        namespace Character
        {
            using namespace Pawn;

            constexpr auto Mesh = 0x0320;    //  USkeletalMeshComponent
            constexpr auto CharacterMovement = 0x0328;    //  UCharacterMovementComponent
        }

        namespace APlayerCameraManager
        {
            constexpr auto PCOwner = 0x0298;    //  APlayerController
            constexpr auto TransformComponent = 0x02A0;    //  USceneComponent
            constexpr auto DefaultFOV = 0x02B0;    //  float
            constexpr auto DefaultOrthoWidth = 0x02B8;    //  float
            constexpr auto DefaultAspectRatio = 0x02C0;    //  float
            constexpr auto CameraCachePrivate = 0x13A0;    //  FCameraCacheEntry
            constexpr auto LastFrameCameraCachePrivate = 0x1BB0;    //  FCameraCacheEntry
        }

        namespace USceneComponent
        {
            constexpr auto RelativeLocation = 0x0130;    //  FVector
            constexpr auto RelativeRotation = 0x0148;    //  FRotator
            constexpr auto RelativeScale3D = 0x0160;    //  FVector
            constexpr auto ComponentVelocity = 0x0178;    //  FVector
        }

        namespace USkeletalMeshComponent
        {
            constexpr auto RenderTime = 0x2F8;  //  FVector
            constexpr auto ComponentToWorld = 0x1D0;    //  FTransform
            constexpr auto BoneArray = 0x5D8;    //  TArray<FTransform>
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
        bool WorldToScreen(CameraView camera, FVector worldLocation, FVector2D* out, FVector2D szScreen, bool isRelative = false);

        //  copy pasta
        D3DMATRIX to_matrix(FRotator rot, FVector origin = FVector(0, 0, 0));
        D3DMATRIX matrix_multiplication(D3DMATRIX pm1, D3DMATRIX pm2);
    }


    /// 
    ///     EXTRAS
    ///  

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
    };

}


//  - Health
//  - Shields
//  - Team
//  - Loadout Information
namespace GrayzoneWarfare
{
    //  using namespace UnrealEngine;

    enum class EGzAliveState : __int8
    {
        Alive = 0,
        Dead = 1,
        Coma = 2,
        EGzAliveState_MAX = 3,
    };


    enum class EGzTeam : __int8
    {
        ETeam_LRI,  //  Lamang Recovery Initiative
        ETeam_MSS,  //  Mithras Security Systems
        ETeam_CSI   //  Crimson Shield International
    };

    enum Bones : __int32
    {
        Root = 0,
        Interaction = 1,
        ik_hand_root = 2,
        ik_hand_gun = 3,
        IK_hand_L = 4,
        IK_hand_R = 5,
        IK_foot_root = 6,
        IK_foot_l = 7,
        IK_foot_r = 8,
        center_of_mass = 9,
        pelvis = 10,
        spine_01 = 11,
        spine_02 = 12,
        spine_03 = 13,
        spine_04 = 14,
        spine_05 = 15,
        neck_01 = 16,
        neck_02 = 17,
        Head = 18,
        Camera = 19,
        root_facials = 20,
        Bone_jaw = 21,
        bone_jawEnd = 22,
        point_jaw_attach = 23,
        bone_mlc1 = 24,
        bone_mlc2 = 25,
        bone_tongueRoot = 26,
        bone_tongue0 = 27,
        bone_tongue1 = 28,
        bone_tongue2 = 29,
        bone_tongue3 = 30,
        l_bone_ml11 = 31,
        L_Bone_ML12 = 32,
        l_bone_ml13 = 33,
        l_bone_ml21 = 34,
        l_bone_ml22 = 35,
        l_bone_ml23 = 36,
        l_bone_w15 = 37,
        l_bone_w25 = 38,
        R_Bone_ML11 = 39,
        r_bone_ml12 = 40,
        R_Bone_ML13 = 41,
        r_bone_ml21 = 42,
        r_bone_ml22 = 43,
        r_bone_ml23 = 44,
        r_bone_w15 = 45,
        r_bone_w25 = 46,
        r_bone_c43 = 47,
        r_bone_c44 = 48,
        r_bone_c45 = 49,
        r_bone_e5 = 50,
        r_bone_e30 = 51,
        r_bone_e31 = 52,
        r_bone_e32 = 53,
        r_bone_e33 = 54,
        r_bone_e34 = 55,
        r_bone_e41 = 56,
        r_bone_e42 = 57,
        r_bone_e43 = 58,
        r_bone_e044 = 59,
        bone_e4c = 60,
        r_bone_e51 = 61,
        r_bone_e52 = 62,
        r_bone_e53 = 63,
        r_bone_e61 = 64,
        r_bone_e62 = 65,
        r_bone_e63 = 66,
        r_bone_f11 = 67,
        r_bone_f12 = 68,
        r_bone_f13 = 69,
        bone_f1c = 70,
        r_bone_f21 = 71,
        r_bone_f22 = 72,
        r_bone_f23 = 73,
        bone_f2c = 74,
        r_bone_mm = 75,
        r_bone_mu11 = 76,
        r_bone_mu12 = 77,
        r_bone_mu13 = 78,
        r_bone_mu21 = 79,
        r_bone_mu22 = 80,
        r_bone_mu23 = 81,
        r_bone_nose = 82,
        r_bone_w12 = 83,
        r_bone_w13 = 84,
        r_bone_w14 = 85,
        r_bone_w20 = 86,
        r_bone_w21 = 87,
        r_bone_w22 = 88,
        r_bone_w23 = 89,
        r_bone_w24 = 90,
        r_bone_c55 = 91,
        r_bone_c54 = 92,
        bone_noseCenter = 93,
        bone_muc2 = 94,
        bone_muc1 = 95,
        r_bone_eyelid_upper = 96,
        r_bone_eyelid_lower = 97,
        r_bone_eye = 98,
        l_bone_c43 = 99,
        l_bone_c44 = 100,
        l_bone_c45 = 101,
        l_bone_c54 = 102,
        l_bone_c55 = 103,
        l_bone_e5 = 104,
        l_bone_e30 = 105,
        l_bone_e31 = 106,
        l_bone_e32 = 107,
        l_bone_e33 = 108,
        l_bone_e34 = 109,
        l_bone_e41 = 110,
        l_bone_e42 = 111,
        l_bone_e43 = 112,
        l_bone_e044 = 113,
        l_bone_e51 = 114,
        l_bone_e52 = 115,
        l_bone_e53 = 116,
        l_bone_e61 = 117,
        l_bone_e62 = 118,
        l_bone_e63 = 119,
        L_Bone_EYE = 120,
        l_bone_eyelid_lower = 121,
        l_bone_eyelid_upper = 122,
        l_bone_f11 = 123,
        l_bone_f12 = 124,
        l_bone_f13 = 125,
        l_bone_f21 = 126,
        l_bone_f22 = 127,
        l_bone_f23 = 128,
        l_bone_mm = 129,
        L_Bone_MU11 = 130,
        L_Bone_MU12 = 131,
        l_bone_mu13 = 132,
        l_bone_mu21 = 133,
        l_bone_mu22 = 134,
        l_bone_mu23 = 135,
        l_bone_nose = 136,
        l_bone_w12 = 137,
        l_bone_w13 = 138,
        l_bone_w14 = 139,
        l_bone_w20 = 140,
        l_bone_w21 = 141,
        l_bone_w22 = 142,
        l_bone_w23 = 143,
        l_bone_w24 = 144,
        clavicle_pec_r = 145,
        spine_04_latissimus_l = 146,
        spine_04_latissimus_r = 147,
        clavicle_pec_l = 148,
        clavicle_r = 149,
        upperarm_r = 150,
        lowerarm_r = 151,
        lowerarm_twist_02_r = 152,
        lowerarm_twist_01_r = 153,
        lowerarm_correctiveRoot_r = 154,
        lowerarm_in_r = 155,
        lowerarm_out_r = 156,
        lowerarm_bck_r = 157,
        lowerarm_fwd_r = 158,
        hand_r = 159,
        pinky_metacarpal_r = 160,
        pinky_01_r = 161,
        pinky_02_r = 162,
        pinky_03_r = 163,
        pinky_03_r_end = 164,
        index_metacarpal_r = 165,
        index_01_r = 166,
        index_02_r = 167,
        index_03_r = 168,
        index_03_r_end = 169,
        thumb_01_r = 170,
        thumb_02_r = 171,
        thumb_03_r = 172,
        thumb_03_r_end = 173,
        wrist_outer_r = 174,
        weapon_r = 175,
        wrist_inner_r = 176,
        ring_metacarpal_r = 177,
        ring_01_r = 178,
        ring_02_r = 179,
        ring_03_r = 180,
        ring_03_r_end = 181,
        middle_metacarpal_r = 182,
        middle_01_r = 183,
        middle_02_r = 184,
        middle_03_r = 185,
        middle_03_r_end = 186,
        upperarm_twist_01_r = 187,
        upperarm_twistCor_01_r = 188,
        upperarm_twist_02_r = 189,
        upperarm_tricep_r = 190,
        upperarm_bicep_r = 191,
        upperarm_twistCor_02_r = 192,
        upperarm_correctiveRoot_r = 193,
        upperarm_in_r = 194,
        upperarm_fwd_r = 195,
        upperarm_bck_r = 196,
        upperarm_out_r = 197,
        clavicle_out_r = 198,
        clavicle_scap_r = 199,
        clavicle_l = 200,
        upperarm_l = 201,
        lowerarm_l = 202,
        lowerarm_twist_02_l = 203,
        lowerarm_twist_01_l = 204,
        lowerarm_correctiveRoot_l = 205,
        lowerarm_in_l = 206,
        lowerarm_out_l = 207,
        lowerarm_bck_l = 208,
        lowerarm_fwd_l = 209,
        hand_l = 210,
        pinky_metacarpal_l = 211,
        pinky_01_l = 212,
        pinky_02_l = 213,
        pinky_03_l = 214,
        pinky_03_l_end = 215,
        index_metacarpal_l = 216,
        index_01_l = 217,
        index_02_l = 218,
        index_03_l = 219,
        index_03_l_end = 220,
        thumb_01_l = 221,
        thumb_02_l = 222,
        thumb_03_l = 223,
        thumb_03_l_end = 224,
        wrist_outer_l = 225,
        weapon_l = 226,
        wrist_inner_l = 227,
        ring_metacarpal_l = 228,
        ring_01_l = 229,
        ring_02_l = 230,
        ring_03_l = 231,
        ring_03_l_end = 232,
        middle_metacarpal_l = 233,
        middle_01_l = 234,
        middle_02_l = 235,
        middle_03_l = 236,
        middle_03_l_end = 237,
        upperarm_twist_01_l = 238,
        upperarm_twistCor_01_l = 239,
        upperarm_twist_02_l = 240,
        upperarm_tricep_l = 241,
        upperarm_bicep_l = 242,
        upperarm_twistCor_02_l = 243,
        upperarm_correctiveRoot_l = 244,
        upperarm_in_l = 245,
        upperarm_fwd_l = 246,
        upperarm_bck_l = 247,
        upperarm_out_l = 248,
        clavicle_out_l = 249,
        clavicle_scap_l = 250,
        thigh_l = 251,
        calf_l = 252,
        foot_l = 253,
        ball_l = 254,
        ball_l_end = 255,
        ankle_bck_l = 256,
        ankle_fwd_l = 257,
        calf_twist_01_l = 258,
        calf_twist_02_l = 259,
        calf_twistCor_02_l = 260,
        calf_correctiveRoot_l = 261,
        calf_kneeBack_l = 262,
        calf_knee_l = 263,
        thigh_twist_01_l = 264,
        thigh_twistCor_01_l = 265,
        thigh_twist_02_l = 266,
        thigh_twistCor_02_l = 267,
        thigh_correctiveRoot_l = 268,
        thigh_bck_lwr_l = 269,
        thigh_in_l = 270,
        thigh_fwd_lwr_l = 271,
        thigh_bck_l = 272,
        thigh_out_l = 273,
        thigh_fwd_l = 274,
        thigh_r = 275,
        calf_r = 276,
        foot_r = 277,
        ball_r = 278,
        ball_r_end = 279,
        ankle_bck_r = 280,
        ankle_fwd_r = 281,
        calf_twist_01_r = 282,
        calf_twist_02_r = 283,
        calf_twistCor_02_r = 284,
        calf_correctiveRoot_r = 285,
        calf_kneeBack_r = 286,
        calf_knee_r = 287,
        thigh_twist_01_r = 288,
        thigh_twistCor_01_r = 289,
        thigh_twist_02_r = 290,
        thigh_twistCor_02_r = 291,
        thigh_correctiveRoot_r = 292,
        thigh_bck_rwr_r = 293,
        thigh_in_r = 294,
        thigh_fwd_rwr_r = 295,
        thigh_bck_r = 296,
        thigh_out_r = 297,
        thigh_fwd_r = 298,
        VB_IK_hand_L_weaponSpace = 299,
        VB_IK_hand_L_chestSpace = 300,
        VB_IK_hand_R_chestSpace = 301,
        VB_IK_hand_gun_weaponSpace = 302,
        VB_IK_hand_R_weaponSpace = 303,
        VB_weapon_R_handSpace = 304,

    };

    static std::vector<std::vector<int>> BoneVector
    {
        { Bones::hand_l, Bones::lowerarm_l, Bones::upperarm_l, Bones::neck_01 },            // Left hand -> neck
        { Bones::hand_r, Bones::lowerarm_r, Bones::upperarm_r, Bones::neck_01 },            // Right hand -> neck
        { Bones::ball_l, Bones::foot_l, Bones::calf_l, Bones::thigh_l, Bones::spine_01 },   // Left foot -> bottom spine
        { Bones::ball_r, Bones::foot_r, Bones::calf_r, Bones::thigh_r, Bones::spine_01 },   // Right foot -> bottom spine
        { Bones::spine_01, Bones::spine_02, Bones::neck_01, Bones::Head }                   // Bottom spine -> head
    };

    static std::vector<std::vector<int>> BoneHandsLVector
    {
        // 
        { Bones::hand_l, Bones::thumb_01_l, Bones::thumb_02_l, Bones::thumb_03_l, Bones::thumb_03_l_end },          //  Thumb
        { Bones::hand_l, Bones::index_01_l, Bones::index_02_l, Bones::index_03_l, Bones::index_03_l_end },          //  Index
        { Bones::hand_l, Bones::middle_01_l, Bones::middle_02_l, Bones::middle_03_l, Bones::middle_03_l_end },      //  Middle
        { Bones::hand_l, Bones::ring_01_l, Bones::ring_02_l, Bones::ring_03_l, Bones::ring_03_l_end },              //  Ring
        { Bones::hand_l, Bones::pinky_01_l, Bones::pinky_02_l, Bones::pinky_03_l, Bones::pinky_03_l_end },          //  Pinky
    };

    static std::vector<std::vector<int>> BoneHandsRVector
    {
        // 
        { Bones::hand_r, Bones::thumb_01_r, Bones::thumb_02_r, Bones::thumb_03_r, Bones::thumb_03_r_end },          //  Thumb
        { Bones::hand_r, Bones::index_01_r, Bones::index_02_r, Bones::index_03_r, Bones::index_03_r_end },          //  Index
        { Bones::hand_r, Bones::middle_01_r, Bones::middle_02_r, Bones::middle_03_r, Bones::middle_03_r_end },      //  Middle
        { Bones::hand_r, Bones::ring_01_r, Bones::ring_02_r, Bones::ring_03_r, Bones::ring_03_r_end },              //  Ring
        { Bones::hand_r, Bones::pinky_01_r, Bones::pinky_02_r, Bones::pinky_03_r, Bones::pinky_03_r_end },          //  Pinky
    };

    //  
    static std::vector<int> BoneAimVector
    {
        Bones::spine_02, Bones::neck_01, Bones::Head
    };

    namespace Offsets
    {
        using namespace UnrealEngine::Offsets;

        //  AMFGPlayerState -> AMFGBasePlayerState -> APlayerState
        namespace AGzPlayerState
        {
            using namespace PlayerState;

            constexpr auto TeamID = 0x0390;  //  FGenericTeamId -> uint8 TeamID
        }

        //  AMFGGameCharacter -> AMFGRepMasterCharacter -> AMFGRepMasterBaseCharacter -> AMFGBaseCharacter
        namespace AGzCharacter
        {
            using namespace Character;

            constexpr auto IsComa = 0x0BF8;    //  bool
            constexpr auto TeamID = 0x0C38;    //  FGenericTeamId -> uint8 TeamID
            constexpr auto HealthSystem = 0x0C90;    //  UMFGHealthSystem*
            constexpr auto IsBodyProtected = 0x1180;    //  bool
            constexpr auto IsHeadProtected = 0x1181;    //  bool
            constexpr auto IgnoreFriendlyDamage = 0x1182;    //  bool
            constexpr auto IgnorePlayerDamage = 0x1183;    //  bool
            constexpr auto isAI = 0x1225;    //  bool
            constexpr auto isDead = 0x1228;    //  bool
        }
    }

    namespace Classes
    {
        using namespace UnrealEngine::Classes;

        struct UMFGScopeRenderComponent
        {
            USceneComponent USceneComponent;	//0x0000
            char pad_0230[700];	//0x0230
            float FOVAngle;	//0x04EC
        };	//Size: 0x0A50

        //  AMFGPlayerController -> AMFGBasePlayerController -> APlayerController
        struct AGzPlayerController
        {
            APlayerController APlayerController;	        //0x0000

        };  //Size: 0x

        //  AMFGPlayerState -> AMFGBasePlayerState -> APlayerState > AInfo > AActor > UObject
        struct AGzPlayerState
        {
            APlayerState APlayerState;	                    //0x0000

            char pad_0350[16];                              //0x0350
            UnrealEngine::FString PlayerNamePrivate;        //0x0360
            char pad_0370[32];	                            //0x0370
            char TeamID;	                                //0x0390

        };	//Size: 0x0391

        //  AMFGGameCharacter -> AMFGRepMasterCharacter -> AMFGRepMasterBaseCharacter -> AMFGBaseCharacter > ACharacter > APawn > AActor > UObject
        struct AGzCharacter
        {
            ACharacter ACharacter;	                        //0x0000
            //  char pad_0680[1400];	                        //0x0680
            char pad_0680[1186];	                        //0x0680
            bool bWantsAiming;                              //0x0B22
            char pad_0B23[1];                               //0x0B23
            bool bWeaponDown;                               //0x0B24
            char pad_0B25[211];                             //0x00B25
            bool IsComa;	                                //0x0BF8
            char pad_0BF9[63];	                            //0x0BF9
            char TeamID;	                                //0x0C38
            char pad_0C39[87];	                            //0x0C39
            __int64 HealthSystem;	                        //0x0C90
            //  char pad_0C98[1256];	                        //0x0C98
            char pad_0C98[32];	                            //0x0C98
            __int64 ScopeRenderComponent;	                //0x0CB8    //  + 0x2EC = FovAngle (float) ; + 0xA10 = CustomProjectionMatrix (FMatrix)
            char pad_0CC0[1216];	                        //0x0CC0
            bool IsBodyProtected;	                        //0x1180
            bool IsHeadProtected;	                        //0x1181
            bool IgnoreFriendlyDamage;	                    //0x1182
            bool IgnorePlayerDamage;	                    //0x1183
            char pad_1184[161];	                            //0x1184
            bool IsAI;	                                    //0x1225
            char pad_1226[2];	                            //0x1226
            bool IsDead;	                                //0x1228
        };  //Size: 0x1229

    }
}