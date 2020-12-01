#include <iostream>
#include "metaTeamComps.h"

pair<string*, string*> findTeamComp(string map, int team, string* usernames) { //<usernames, operators>
	metaTeamComps metaTeams = metaTeamComps();
	string* operators = metaTeams.idealOperators(map, team);

	return { usernames, operators };
}

int main() {
	return 0;
}

//CAOSINDOSAKDNFLSKDNFLKSDNFLKDSNflA