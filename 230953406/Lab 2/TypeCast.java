import java.util.Scanner;
class TypeCast{
	public static void main(String args[]){
		int a;
		double b;
		char c;
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter an integer:");
		a = sc.nextInt();
		System.out.println("Enter an double:");
		b = sc.nextDouble();
		System.out.println("Enter an character:");
		c = sc.next().charAt(0);
		byte d = (byte)a;
		System.out.println("int to byte: "+d);
		int e = (int)c;
		System.out.println("char to int: "+e);
		byte f = (byte)b;
		System.out.println("double to byte: "+f);
		int g = (int)b;
		System.out.println("double to int: "+g);
	}
}