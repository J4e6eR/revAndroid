// This is our implementation for reading and probably emulating raw NFC data
#include <cstdio>
// #include <cstddef>
// #include <binder_ndk.h>
// #include <android/binder_ibinder.h>
#include "nfc_android_headers.h"

// using aidl::android::hardware::nfc::INfc;

class NfcClientCallbackArgs {
   public:
    aidl::android::hardware::nfc::NfcEvent last_event_;
    aidl::android::hardware::nfc::NfcStatus last_status_;
    aidl::android::hardware::nfc::NfcData last_data_;
};

// class Testing: public aidl::android::hardware::nfc::INfcClientCallback{
//     public:
//         virtual ~Testing() = default;
//         aidl::android::hardware::Return<void> sendEvent(aidl::android::hardware::nfc::NfcEvent event, aidl::android::hardware::nfc::NfcStatus event_status) override {
//         NfcClientCallbackArgs args;
//         args.last_event_ = event;
//         args.last_status_ = event_status;
//         NotifyFromCallback(kCallbackNameSendEvent, args);
//         return Void();
//     };
// };

int main(int argc, char** argv){
    printf("Working\n");
    const AParcel* parcel = AParcel_create();
    printf("AParcel: %p\n", parcel);
    
    // Get the NFC service via AServiceManager
    // ndk::AIBinder* binder = ndk::AServiceManager_waitForService("...");
    // ndk::SpAIBinder spBinder(binder);
        // printf("Binder: %p\n", binder);
        // std::shared_ptr<aidl::android::hardware::nfc::INfc>*  nfcInstance;

    // auto x = ndk::SpAIBinder(nullptr);
    ndk::AIBinder* x = AServiceManager_waitForService("nfc");
    if (x == nullptr){
        printf("Is this null??\n");
    }
    binder_status_t status = AIBinder_ping(x);
    printf("Our first AI binder is here: %p with status: %i\n", x, status);
    ndk::SpAIBinder* binder = new ndk::SpAIBinder(x);
    // printf("SPAIBinder so file: %p\n", binder);
    // auto callback = aidl::android::hardware::nfc::BpNfcClientCallback(*binder);   
    // auto callback = aidl::android::hardware::nfc::BpNfc::BpNfc(binder);   
    // auto infc_parcel = aidl::android::hardware::nfc::INfcClientCallback();
    // auto Tester = Testing();
    // infc_parcel.fromBinder(binder);
    // auto callback = aidl::android::hardware::nfc::INfcClientCallbackDefault();   
    // auto parcel = aidl::android::hardware::nfc::INfc::INfc::readFromParcel(parcel, &nfcInstance);
    // Create a AParcel objet to interact with hardware
}