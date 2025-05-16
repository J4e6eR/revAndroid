MINECRAFT_REV
signing-my-android-application-as-system-app: https://stackoverflow.com/questions/37586255/signing-my-android-application-as-system-app

Start vscode in termux: https://gist.github.com/ppoffice/b9e88c9fd1daf882bc0e7f31221dda01
> Command to install argon2:
    # Ensure necessary dependencies are installed
    pkg update
    pkg install nodejs npm python make clang
    
    npm install node-gyp
    
    node-gyp build
    # Create the .gyp directory and file if it does not exist
    mkdir -p ~/.gyp
    echo "{'variables':{'android_ndk_path':''}}" > ~/.gyp/include.gypi

    # Set the GYP_DEFINES environment variable
    export GYP_DEFINES="android_ndk_path=''"

    # Proceed with the installation
    CXX=clang++ npm install argon2 --build-from-source
> Command: code-server --bind-addr 0.0.0.0:8888

The error related to inconsistencies in the value of inputBifer is because of teh same buffer being used to send and receive the data in the server side. This can be solved by having seperate buffers.

The while loop is called only one time.
https://github.com/uhub/awesome-c


Get NFC tensor data
adb logcat -s "NfcService:D" "NfcTag:D" "NfcA:V" "NfcB:V" "NfcF:V"
NFC .so file from vendors: https://dumps.tadiphone.dev/dumps/xiaomi/houji/-/blob/63e005bcf3abc5e96708052091b9479165cb27da/vendor/lib64/android.hardware.nfc-V1-ndk.so 
SDK releases for teh source code possibly of Android NFC: https://android.googlesource.com/platform/hardware/st/nfc/+/sdk-release/
Have a look at this: https://cs.android.com/android/platform/superproject/+/master:hardware/interfaces/nfc/1.0/vts/functional/VtsHalNfcV1_0TargetTest.cpp

Command to run.
clang++ -Wall -std=c++11 test_nfc.cpp -o test.out -landroid.hardware.nfc-V1-ndk.so -L./
WORKING: clang++ -Wall -std=c++11 read_nfc.cpp -o test.out -L./ -l:android.hardware.nfc-V1-ndk.so && LD_LIBRARY_PATH=. ./test.out
Demangle all the functions: objdump -T android.hardware.nfc-V1-ndk.so | curl --data-urlencode input@- https://demangler.com/raw

https://android.googlesource.com/platform/frameworks/native/+/master/libs/binder/ndk/include_ndk/android/binder_parcel.h
