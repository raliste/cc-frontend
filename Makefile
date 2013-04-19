all: clean server

server:
	g++ -Wall sfe.cc xfe.cc -levent -lglog -lgflags -lctemplate -o server

clean:
	rm server