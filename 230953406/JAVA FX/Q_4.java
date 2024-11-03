import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class GCDApp extends Application {
    public void start(Stage stage) {
        TextField num1 = new TextField(), num2 = new TextField();
        Label result = new Label();
        Button calcGCD = new Button("Calculate GCD");
        calcGCD.setOnAction(e -> result.setText("GCD: " + gcd(
            Integer.parseInt(num1.getText()), Integer.parseInt(num2.getText()))));
        
        GridPane grid = new GridPane();
        grid.addRow(0, new Label("Number 1:"), num1);
        grid.addRow(1, new Label("Number 2:"), num2);
        grid.addRow(2, calcGCD);
        grid.addRow(3, result);

        stage.setScene(new Scene(grid, 300, 200));
        stage.setTitle("GCD Calculator");
        stage.show();
    }

    private int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

    public static void main(String[] args) { launch(args); }
}
