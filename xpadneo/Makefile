VERSION=0.9.6

all:
	true

install:
	sed 's/"@DO_NOT_CHANGE@"/"'"${VERSION}"'"/g' <xpadneo/hid-xpadneo/dkms.conf.in >xpadneo/hid-xpadneo/dkms.conf
	install -d $(DESTDIR)/usr/src/
	cp -r xpadneo/hid-xpadneo $(DESTDIR)/usr/src/
	install -d $(DESTDIR)/etc/modules-load.d
	ln -s /usr/src/hid-xpadneo $(DESTDIR)/usr/src/hid-xpadneo-"${VERSION}"
	cp -r modules-load-d-xpadneo.conf  $(DESTDIR)/etc/modules-load.d/xpadneo.conf
