# TDLib - Setup

- Instructions [Java](https://tdlib.github.io/td/build.html?language=Java)

### Step 1:

TDLib should be prebuilt with JNI bindings. These below commands are for Mac M1, but can see specific to your requirement in the above instructions.
```shell
rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DJAVA_HOME=/Library/Java/JavaVirtualMachines/temurin-17.jdk/Contents/Home -DOPENSSL_ROOT_DIR=/opt/homebrew/opt/openssl/ -DCMAKE_INSTALL_PREFIX:PATH=../example/java/td -DTD_ENABLE_JNI=ON ..
cmake --build . --target install
```

### Step 2:
After this you can compile the example source code in the `example/java` directory. 
```shell
cd example/java
rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DJAVA_HOME=/Library/Java/JavaVirtualMachines/temurin-17.jdk/Contents/Home -DTd_DIR=/Users/omer/dev-repos/laldinsoft/cargo-scanner/cargoscanner-td/example/java/td/lib/cmake/Td -DCMAKE_INSTALL_PREFIX:PATH=.. ..
cmake --build . --target install
```

### Step 3:
Run the example code to get authentication session db.
```shell
cd ..
cd bin
java '-Djava.library.path=.' net/cargoscanner/api/telegram/example/Example
```

After successfully logging in, you will see the `tdlib` folder created in the `example/java` directory. This folder contains the authentication session db file.
