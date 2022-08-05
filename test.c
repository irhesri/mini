void	print0()
{
	printf("0\n");
}
void	print1()
{
	printf("1\n");
}
void	print2()
{
	printf("2\n");
}
void	print3()
{
	printf("3\n");
}
void	get_function(short b)
{
	static void	(*ptr[4])();
	if (!ptr)
	{
		ptr[0] = print0;
		ptr[1] = print1;
		ptr[2] = print2;
		ptr[3] = print3;
	}
}

int	main()
{
	get_function("")
}