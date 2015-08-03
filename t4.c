int printf();
int main(){
	int x;
	int y;
	x = 1;
	y = 4;
	if(x == 4){
		y = 3;
	}

	for(x=1; x<y; x++){
		printf("%d",x);
	}

	return x;
}
