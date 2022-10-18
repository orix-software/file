
ORICUTRON_PATH="/mnt/c/Users/plifp/OneDrive/oric/oricutron_wsl/oricutron"
CA65_INC=/usr/share/cc65/asminc/
mkdir build/bin/ -p
cl65 -o build/bin/file -ttelestrat src/file.c
cl65 -o 1000 -ttelestrat src/file.c --start-addr \$800
cl65 -o 1256 -ttelestrat src/file.c --start-addr \$900
deps/orix-sdk/bin/relocbin.py3 -o build/bin/file -2 1000 1256
cp build/bin/file $ORICUTRON_PATH/sdcard/bin
cd $ORICUTRON_PATH
./oricutron
cd -

