long array[] = {0xd, 0xc0, 0xb00, 0xa000, 0};
/* Count elements in null-terminated list */ long len1( long a[] )
{
long len;
	for (len = 0; a[len]; len++ ); return len;
}
main() {
	long ans;
	ans = len1( array );
	printf( "Answer: %ld\n", ans );
}