import java.util.Scanner;
class Calc{
	public static void main(String args[]){
		float n1, n2, Ans;
		char c, resp;
		Scanner sc = new Scanner(System.in);
		do{
		System.out.println("Enter first number, operator, second number: ");
		n1 = sc.nextFloat();
		c = sc.next().charAt(0);
		n2 = sc.nextFloat();
			switch(c){
				case '+':
					Ans = n1+n2;
					System.out.println("Answer = "+Ans);
					break;
				case '-':
					Ans = n1-n2;
					System.out.println("Answer = "+Ans);
					break;
				case '*':
					Ans = n1*n2;
					System.out.println("Answer = "+Ans);
					break;
				case '/':
					Ans = n1/n2;
					System.out.println("Answer = "+Ans);
					break;
				default:
					System.out.println("Out of bound");
			}
			System.out.println("Do another (y/n)?");
			resp = sc.next().charAt(0);
		}while(resp=='y');
	}
}
