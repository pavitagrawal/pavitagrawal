import java.util.Scanner;
class Box {
    double width;
    double height;
    double depth;
    Box(double w, double h, double d) {
        width = w;
        height = h;
        depth = d;
    }
    double volume() {
        return width * height * depth;
    }
}
class BoxDemo {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter width: ");
        double width = sc.nextDouble();
        System.out.print("Enter height: ");
        double height = sc.nextDouble();
        System.out.print("Enter depth: ");
        double depth = sc.nextDouble();
        Box mybox = new Box(width, height, depth);
        double vol = mybox.volume();
        System.out.println("Volume is " + vol);
    }
}