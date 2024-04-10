NF>0	{ 
	    split($4, a, ".");
	    goesin = a[1] ".nvs";
	    /* print $1 " comes from " $4 " and goes in " goesin; */
	    printf("%s", $5) > goesin;
	    line = "";
	    for(i=6; i <= NF; i++) 
	    { 
	    	/* printf(" %s", $i) > goesin; */
		line = line " " $i;
	    }
	    split(line, b, "{");
	    printf("%s;\n", b[1]) > goesin;
	    /* printf(";\n") > goesin; */
	
	}
