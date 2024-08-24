import java.util.Scanner;
class Rectangle
{
	public static void main(String args[])
	{
		int l, b, circum, area;
		Scanner sc = new Scanner(System.in);
	System.out.println("Enter the length");
		l = sc.nextInt();
		System.out.println("Enter the breadth");
		b = sc.nextInt();
		circum = 2*(l+b);
		area = l*b;
		System.out.println("circumference is: "+circum);
		System.out.println("area is: "+area);
	}
}