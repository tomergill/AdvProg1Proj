import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.geometry.Insets;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayDeque;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * This class is the controller for the GUI (View) and the server (Model).
 *
 * @author Tomer Gill
 * @since 11/03/17
 */
public class mainController {
    private int time = 0;
    private ImageView[][] imageMatrix = null;
    private Map map = null;
    public static AtomicBoolean stop = new AtomicBoolean(false);
    public static Thread mapThread = null;
    public static Thread communicationsThread = null;
    private static Queue<String> sendToServer = new ArrayDeque<>();

    @FXML
    BorderPane mainBP;

    @FXML
    Label tLbl, eLbl;

    @FXML
    Label curTimeLbl;

    @FXML
    Label errLbl;

    @FXML
    TextField sendFld, addFld;

    @FXML
    Button sendBtn, addBtn;

    @FXML
    GridPane grid;

    private Socket socket;
    private PrintWriter out;
    private BufferedReader in;

    @FXML
    void initialize() {
        curTimeLbl.setText(Integer.toString(time));
        errLbl.setMinWidth(errLbl.getWidth());
        showErrorLabel(false);
        errLbl.setPrefHeight(eLbl.getHeight());
        curTimeLbl.setPrefHeight(tLbl.getHeight());

        /*Send Button Action*/
        sendBtn.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                String txt = sendFld.getText();
                showErrorLabel(false);
                if (txt.equals(""))
                    showErrorLabel(true);
                else {
                    sendFld.setText("");
                    sendToServer.add(txt);
                    if (txt.equals("9")) {
                        advanceTime();
                    } else if (txt.equals("1") || txt.equals("2") || txt.equals("3")) {
                        while (sendFld.getText().equals("")) ;
                        sendToServer.add(sendFld.getText());
                        sendFld.setText("");
                    }
                }
            }
        });

        /*Add Button Action*/
        addBtn.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                String s = addFld.getText();
                addFld.setText("");
                String[] args = new String[4];
                args[0] = "client.out";
                args[1] = Main.Args[0];
                args[2] = Main.Args[1];
                args[3] = s;
                try {
                    Runtime.getRuntime().exec(args);
                } catch (Exception e) {
                    System.out.println(e.getMessage());
                }
            }
        });

        /*initializes the socket and it's streams*/
        try {
            socket = new Socket(Main.Args[0], Integer.parseInt(Main.Args[1]));
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));
        } catch (Exception e) {
            System.out.println("ERROR creating socket");
            stop.set(true);
            Runtime.getRuntime().exit(1);
        }

        /*Thread responsible for sending to server and receiving from it*/
        communicationsThread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    /*Create the map from the input from the server*/
                    String mapSizes, received = null;
                    while ((mapSizes = in.readLine()) == null) ;
                    map = Map.createMapFromInput(mapSizes);
                    String send;
                    while (!stop.get()) {
                        while (!sendToServer.isEmpty()) {
                            send = sendToServer.remove();
                            out.println(send);
                            switch (send) {
                                case "1":
                                case "2":
                                case "3":
                                    out.println(sendToServer.remove());
                                    break;
                                case "7":
                                    stop.set(true);
                                    Runtime.getRuntime().exit(0);
                            }
                        }
                        while ((received = in.readLine()) != null) {
                            if (received.equals("ERROR"))
                                showErrorLabel(true);
                            else if (received.startsWith("DRIVER: ")) {
                                String[] arr = received.substring(8).split(" ");
                                map.addDriver(new Driver(Integer.parseInt(arr[0]),
                                        Integer.parseInt(arr[1])));
                            } else if (received.startsWith("CAB: ")) {
                                map.addTaxi(new Taxi(Integer.parseInt(received.substring(5))));
                            } else if (received.startsWith("MOVED: ")) {
                                String[] arr = received.substring(7).split(" ");
                                map.setDriverLocation(Integer.parseInt(arr[0]), new Point(
                                        Integer.parseInt(arr[1]), Integer.parseInt(arr[2])));
                            }
                        }
                    }

                } catch (Exception e) {
                    System.out.println("ERROR creating socket");
                    stop.set(true);
                    Platform.exit();
                    Runtime.getRuntime().exit(1);
                }

            }
        });
        communicationsThread.start();

        /*Setting up the grid*/
        grid = new GridPane();
        mainBP.setCenter(grid);
        grid.setVgap(10);
        grid.setHgap(10);
        grid.setPadding(new Insets(0, 10, 0, 10));
//        //TODO remove temporary initialization of values
//        //TODO get map sizes and obstacles
//        map = new Map(5, 7);
//        map.addObstacle(1, 1);
//        map.addObstacle(2, 2);
//        map.addObstacle(3, 3);
//        map.addObstacle(3, 4);
//        map.addTaxi(new Taxi(0));
//        map.addTaxi(new Taxi(1));
//        map.addTaxi(new Taxi(2));
//        map.addTaxi(new Taxi(3));

        //create Thread that draws the map.
        mapThread = new Thread(new Runnable() {
            @Override
            public void run() {
                while (!stop.get()) {
                    if (map != null && map.hasChanged())
                        drawMap();
                }
            }
        });
        mapThread.start();
    }

    private void showErrorLabel(boolean err) {
        if (err) {
            errLbl.setText("-1");
            errLbl.setTextFill(Paint.valueOf("#e80505"));
        } else {
            errLbl.setText("0");
            errLbl.setTextFill(Color.DARKGREEN);
        }
    }

    private void advanceTime() {
        curTimeLbl.setText(Integer.toString(++time));
    }

    public synchronized void drawMap() {
        if (map == null)
            return;

        map.check();
        int mapW = map.getWidth(), mapH = map.getHeight();

        if (imageMatrix == null) { //create the map on the grid.
            imageMatrix = new ImageView[mapW][mapH];
            for (int i = 0; i < mapW; i++) {
                for (int j = 0; j < mapH; j++) {
                    imageMatrix[i][j] = new ImageView(map.getImageOfTile(0, 0));
                    grid.add(imageMatrix[i][j], j, mapW - i - 1);
                }
            }
        }

        /*Set the images by their location*/
        for (int i = 0; i < mapW; i++) {
            for (int j = 0; j < mapH; j++) {
                imageMatrix[i][j].setImage(map.getImageOfTile(i, j));
            }
        }
    }
}
