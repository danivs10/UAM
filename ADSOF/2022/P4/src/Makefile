all: 
	javac p4/exception/*.java	
	javac p4/game/*.java
	javac p4/interfaces/*.java
	javac p4/tokens/*.java
	javac tests/*.java

doc:
	javadoc -d ../doc -author p4/*/*.java

clean:
	rm -f tests/*.class
	rm -f p4/tokens/*.class
	rm -f p4/interfaces/*.class
	rm -f p4/game/*.class
	rm -f p4/exception/*.class