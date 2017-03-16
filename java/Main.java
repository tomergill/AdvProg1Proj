import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Rectangle2D;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.io.IOException;

public class Main extends Application {
    public static String[] Args = null;

    public static void main(String[] args) {
        Args = args.clone();
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("main.fxml"));
        primaryStage.setTitle("TAXI CENTER SIMULATOR 2017");

        Rectangle2D primaryScreenBounds = Screen.getPrimary().getVisualBounds();
        //set Stage boundaries to visible bounds of the main screen
        primaryStage.setX(primaryScreenBounds.getMinX());
        primaryStage.setY(primaryScreenBounds.getMinY());
        primaryStage.setWidth(primaryScreenBounds.getWidth());
        primaryStage.setHeight(primaryScreenBounds.getHeight());

//        System.out.println("x: " + primaryStage.getX() + "y: " + primaryStage.getY() + "width: " +
//                primaryStage.getWidth() + "height: " + primaryStage.getHeight());

        //primaryStage.setFullScreen(true);
        Scene scene = new Scene(root, primaryStage.getWidth(), primaryStage.getHeight());
        scene.getStylesheets().add(getClass().getResource("main.css").toExternalForm());
        primaryStage.setResizable(false);
        primaryStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent event) {
                mainController.stop.set(true);
                try {mainController.mapThread.join();}
                catch (Exception e) {
                    System.out.println(e.getMessage());
                }
            }
        });

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
