BEGIN {FS = ","}{

	if (NR == 1){
		val[NR] = $6;
}
	else {
		variable = val[NR - 1] + $4;
		if(val[NR + 1] = $6) {
			print "Koniec pliku lub dodanie zera, stad: "
		}
		if(variable != $6) {
			print "\t", variable, "=/=", $6, "Blad w linii: ", NR;}
		val[NR] = $6
}}
END{};
