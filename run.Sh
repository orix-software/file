
ORICUTRON_PATH="/mnt/c/Users/plifp/OneDrive/oric/oricutron_wsl/oricutron"
CA65_INC=/usr/share/cc65/asminc/
mkdir build/bin/ -p
cl65 -o build/bin/file -ttelestrat src/file.c
cp build/bin/file $ORICUTRON_PATH/sdcard/bin
cd $ORICUTRON_PATH
./oricutron
cd -

