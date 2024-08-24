import java.util.Scanner;
class MultDiv{
	public static void main(String args[]){
		int num, mult, div;
		System.out.println("Enter the number: ");
		Scanner sc = new Scanner(System.in);
		num = sc.nextInt();
		mult = num<<1;
		div = num>>1;
		System.out.println(num+"x2 = "+mult);
		System.out.println(num+"/2 = "+div);
	}	
}