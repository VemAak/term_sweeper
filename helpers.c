int proj_interval(int value, int upper, int lower){
    if (value < lower){
	value = lower;
    }
    else if (value > upper){
	value = upper;
    }
    return value;
}
