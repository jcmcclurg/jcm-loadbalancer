namespace cpp mp3

service Hub {
  // Register yourself with the network, and notify the others.
	oneway void join(1:i16 port),
  oneway void leave(1:i16 port),
  list<i16> getMembers(),
}
