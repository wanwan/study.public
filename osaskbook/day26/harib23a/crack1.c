void _api_end(void);

void HariMain(void)
{
	*((char *) 0x00102600) = 0;
	_api_end();	
}
