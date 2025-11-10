VERSION=0.3

.PHONY: install
all:
	true

install:
		cp xone/dkms.conf xone/dkms.conf.in
		sed 's/"#VERSION#"/"'"${VERSION}"'"/g' <xone/dkms.conf.in >xone/dkms.conf
		echo 'ccflags-y += -DDEBUG' >> "xone/Kbuild"
		echo "* Copying module into /usr/src..."
		install -dm755 $(DESTDIR)/usr/src/xone
		rsync -av --progress ./xone/* $(DESTDIR)/usr/src/xone/ --exclude debian
		install -dm755 $(DESTDIR)/usr/bin
		cp xone/install/firmware.sh $(DESTDIR)/usr/bin/xone-firmware
		ln -sf /usr/src/xone $(DESTDIR)/usr/src/xone-"${VERSION}"
		install -d $(DESTDIR)/etc/modules-load.d
		cp -r modules-load-d-xone.conf  $(DESTDIR)/etc/modules-load.d/xone.conf
		echo "* Blacklisting xpad module..."
		install -D -m 644 xone/install/modprobe.conf $(DESTDIR)/etc/modprobe.d/xone-blacklist.conf
