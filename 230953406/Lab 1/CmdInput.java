class CmdInput
{
	public static void main(String args[])
		{
		int a, b, c;
		double d;
			a=Integer.parseInt(args[0]);
			b=Integer.parseInt(args[1]);
			d=Double.parseDouble(args[2]);
			c=a+b;
		System.out.println("The sum = "+c);
		System.out.println("d = "+d);
		}
}