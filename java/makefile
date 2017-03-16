jar: compile
	jar cfm gui.jar Manifest.mf -C bin . -C resources . *.fxml *.css
	mv gui.jar ..

compile:
	javac -d bin *.java

