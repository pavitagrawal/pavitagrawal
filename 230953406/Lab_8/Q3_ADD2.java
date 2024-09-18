interface Shape{
    double getArea();
}
class Rectangle implements Shape{
    double length;
    double breadth;
    Rectangle(double length, double breadth){
        this.length = length;
        this.breadth = breadth;
    }
    public double getArea(){
        return length * breadth;
    }
}
class Circle implements Shape{
    double radius;
    Circle(double radius){
        this.radius = radius;
    }
    public double getArea(){
        return 3.14*radius*radius;
    }
}
class Square implements Shape{
    double side;
    Square(double side){
        this.side = side;
    }
    public double getArea(){
        return side*side;
    }
}
class Triangle implements Shape{
    double base;
    double height;
    Triangle(double base, double height){
        this.base = base;
        this.height = height;
    }
    public double getArea(){
        return 0.5*base*height;
    }
}
class areaCalculator{
    public static void main(String args[]){
        Rectangle rectangle = new Rectangle(12.5, 14);
        Circle circle = new Circle(6.5);
        Square square = new Square(7);
        Triangle triangle = new Triangle(6, 8);
        System.out.println("Area of Rectangle: "+rectangle.getArea());
        System.out.println("Area of Circle: "+circle.getArea());
        System.out.println("Area of Square: "+square.getArea());
        System.out.println("Area of Triangle: "+triangle.getArea());
    }
}