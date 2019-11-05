void _api_putchar(int c);
void _api_end(void);

void HariMain(void)
{
	char a[100];
	a[10] = 'A';		/* ‚±‚ê‚Í‚à‚¿‚ë‚ñ‚¢‚¢ */
	_api_putchar(a[10]);
	a[102] = 'B';		/* ‚±‚ê‚Í‚Ü‚¸‚¢‚æ‚Ë */
	_api_putchar(a[102]);
	a[123] = 'C';		/* ‚±‚ê‚à‚Ü‚¸‚¢‚æ‚Ë */
	_api_putchar(a[123]);
	_api_end();
}
