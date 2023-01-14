#include <iostream>
#include <tins/tins.h>
#include <list>

using namespace std;

void usage(){
	cout << "syntax: beacon-flood <interface>" << endl;
	cout << "example: beacon-flood wlan0" << endl;
	exit(0);
}

int main(int argc, char *argv[]) {
	if(argc != 2) usage();
	// -- Base Setting
	list<string> ssidList{
		"1.TESTJAM",
		"2.TESTJAM",
		"3.TESTJAM",
		"4.TESTJAM",
		"5.TESTJAM",
		"6.TESTJAM",
	};
	list<string>::iterator it = ssidList.begin();

	Tins::PacketSender sender;
	Tins::NetworkInterface iface(argv[1]);

	// -- Packet Information
	while(1){
		Tins::Dot11Beacon beacon;
		beacon.addr1("ff:ff:ff:ff:ff:ff");
		beacon.addr2("12:48:16:32:64:12");
		beacon.addr3(beacon.addr2());
		beacon.ssid(*it);
		beacon.ds_parameter_set(8);
		beacon.supported_rates({1.0f, 5.5f, 11.0f});
		beacon.rsn_information(Tins::RSNInformation::wpa2_psk());

		Tins::RadioTap radio_tap;
		radio_tap.inner_pdu(beacon);

		sender.send(radio_tap,iface);
		if (++it == ssidList.end())
			it = ssidList.begin();
	}

	return 0;
}
