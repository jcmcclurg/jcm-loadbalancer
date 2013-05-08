namespace cpp mp3

struct Result {
  1: i16 job
}

struct Job{
  1: i16 id,
  2: i16 hopcount
}

exception MyError{
  1: string message
}

service Node {
  // group membership
  oneway void joinNotify(1:i16 port),
  oneway void leaveNotify(1:i16 port),

  // add a job to the queue
	i16 getNumJobs(),
	oneway void queueJob(1:Job job),

  // call to process the latest batch of jobs
	list<Result> processJobs() throws (1: MyError e)

  // shuffle jobs around
  oneway void setBatchSize(1:i16 size),
  i16 getNumExtraJobs(),
  list<Job> giveJobs(1: i16 numJobs),

  // ricard-agarwala distributed mutex
  oneway void notifyMutexRequest(1:i16 lamportTs, 2:i16 fromPort),
  oneway void notifyMutexReply(1:i16 fromPort)
}
