// TODO: Add the support for SpAIBinder  [Stands for Special AI binder, lets see what it is]
#include <cstddef> 
#include <cstdio>
#include <string>

typedef int32_t binder_status_t;
struct AParcel;
typedef struct AParcel AParcel;
extern "C"{
    AParcel* AParcel_create();
}

// Example assert to prevent error
void __assert(const char* file, int line, const char* message) {
    fprintf(stderr, "Assertion failed at %s:%d: %s\n", file, line, message);
}

namespace ndk {
    struct AIBinder;
    extern "C"{
        bool AIBinder_incStrong(AIBinder *binder);
        void AIBinder_decStrong(AIBinder* binder);
        bool AIBinder_isRemote(const AIBinder* binder);
    }
    // AIBinder* AServiceManager_waitForService(const char* instance);

    // Reference: https://android.googlesource.com/platform//frameworks/native/+/b51a9cc926a8f49db6c2c65a47ec4ea7d72b510b/libs/binder/ndk/include_cpp/android/binder_auto_utils.h
    class SpAIBinder {
    public:
        /**
        * Default constructor.
        */
        SpAIBinder() : mBinder(nullptr) {}
        /**
        * Takes ownership of one strong refcount of binder.
        */
        explicit SpAIBinder(AIBinder* binder) : mBinder(binder) {}
        /**
        * Convenience operator for implicitly constructing an SpAIBinder from nullptr. This is not
        * explicit because it is not taking ownership of anything.
        */
        SpAIBinder(std::nullptr_t) : SpAIBinder() {}  // NOLINT(google-explicit-constructor)
        /**
        * This will delete the underlying object if it exists. See operator=.
        */
        SpAIBinder(const SpAIBinder& other) { *this = other; }
        /**
        * This deletes the underlying object if it exists. See set.
        */
        ~SpAIBinder() { set(nullptr); }
        /**
        * This takes ownership of a binder from another AIBinder object but it does not affect the
        * ownership of that other object.
        */
        SpAIBinder& operator=(const SpAIBinder& other) {
            if (this == &other) {
                return *this;
            }
            AIBinder_incStrong(other.mBinder);
            set(other.mBinder);
            return *this;
        }
        /**
        * Takes ownership of one strong refcount of binder
        */
        void set(AIBinder* binder) {
            AIBinder* old = *const_cast<AIBinder* volatile*>(&mBinder);
            if (old != nullptr) AIBinder_decStrong(old);
            if (old != *const_cast<AIBinder* volatile*>(&mBinder)) {
                __assert(__FILE__, __LINE__, "Race detected.");
            }
            mBinder = binder;
        }
        /**
        * This returns the underlying binder object for transactions. If it is used to create another
        * SpAIBinder object, it should first be incremented.
        */
        AIBinder* get() const { return mBinder; }
        /**
        * This allows the value in this class to be set from beneath it. If you call this method and
        * then change the value of T*, you must take ownership of the value you are replacing and add
        * ownership to the object that is put in here.
        *
        * Recommended use is like this:
        *   SpAIBinder a;  // will be nullptr
        *   SomeInitFunction(a.getR());  // value is initialized with refcount
        *
        * Other usecases are discouraged.
        *
        */
        AIBinder** getR() { return &mBinder; }
        bool operator!=(const SpAIBinder& rhs) const { return get() != rhs.get(); }
        bool operator<(const SpAIBinder& rhs) const { return get() < rhs.get(); }
        bool operator<=(const SpAIBinder& rhs) const { return get() <= rhs.get(); }
        bool operator==(const SpAIBinder& rhs) const { return get() == rhs.get(); }
        bool operator>(const SpAIBinder& rhs) const { return get() > rhs.get(); }
        bool operator>=(const SpAIBinder& rhs) const { return get() >= rhs.get(); }
        private:
            AIBinder* mBinder = nullptr;
    };

    template <typename INTERFACE>
    class BpCInterface : public INTERFACE {
    public:
        // SpAIBinder(std::nullptr_t);
        explicit BpCInterface(const SpAIBinder& binder) : mBinder(binder) {}
        virtual ~BpCInterface() {}
        SpAIBinder asBinder() override;
        bool isRemote() override { return AIBinder_isRemote(mBinder.get()); }
        binder_status_t dump(int fd, const char** args, uint32_t numArgs) override {
            return AIBinder_dump(asBinder().get(), fd, args, numArgs);
        }
    private:
        SpAIBinder mBinder;
    };
}
namespace aidl{
    namespace android{
        class sp; // Strong Pointers
        class wp; // Weak pointers
        
        namespace hardware{
            class Return;
            class Void;
            // class hidl_vec;
            
            namespace nfc{
                // namespace V1_0{
                enum NfcEvent{
                    OPEN_CPLT,
                };
                enum NfcStatus{
                    OK,
                    // OPEN_CPLT,
                };
                class NfcData{
                    public:
                        NfcData();
                        NfcData& operator=(const std::vector<uint8_t>& vec);
                };

                class INfc{
                   public: 
                    INfc();
                    // NfcStatus open_1_1(NfcClientCallback param_1); '
                    unsigned long writeToParcel(AParcel *param_1);
                    unsigned long static readFromParcel(const AParcel *param_1, std::shared_ptr<aidl::android::hardware::nfc::INfc>* instance);
                    void fromBinder(ndk::SpAIBinder * param_1);
                };
                class BpNfc{
                    public:
                        // Constructor
                        BpNfc(ndk::SpAIBinder *param_1);
                        ~BpNfc();

                        void getInterfaceHash(std::string *param_1);
                        void getInterfaceVersion(int *param_1);
                        void isVerboseLoggingEnabled(bool* param_1);
                        void setEnableVerboseLogging(bool param_1);
                };

                class INfcClientCallbackDefault{
                    public:
                        INfcClientCallbackDefault();
                        ~INfcClientCallbackDefault();
                };

                class BpNfcClientCallback: public BpNfc{
                    public:
                        BpNfcClientCallback(ndk::SpAIBinder const&);
                        ~BpNfcClientCallback();
                };

                class INfcClientCallback: public INfc{
                    public:
                        // virtual aidl::android::hardware::Return<void> sendEvent(aidl::android::hardware::nfc::NfcEvent event, aidl::android::hardware::nfc::NfcStatus event_status) override;
                        void sendData();
                        void fromBinder(ndk::SpAIBinder * param_1);
                        void getDefaultImpl(void);

                };
            // } 
            }
        }
    }
}

extern "C"{
    AParcel* AParcel_create();
    __attribute__((warn_unused_result)) ndk::AIBinder* AServiceManager_waitForService(const char* instance);
    binder_status_t AIBinder_ping(ndk::AIBinder *binder);
}

