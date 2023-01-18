sudo apt-get install -y build-essential libtool libglib2.0-dev libpixman-1-dev zlib1g-dev git libfdt-dev gcc-multilib gdb
git clone https://github.com/mit-pdos/6.828-qemu.git qemu
cd qemu
./configure --disable-kvm --target-list="i386-softmmu x86_64-softmmu"
make && make install