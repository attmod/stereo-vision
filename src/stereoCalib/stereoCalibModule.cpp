#include "stereoCalibModule.h"
#include <yarp/os/Stamp.h>
#include <yarp/os/Os.h>



bool stereoCalibModule::configure(yarp::os::ResourceFinder &rf)
{    


   moduleName            = rf.check("name", 
                           Value("stereoCalib"), 
                           "module name (string)").asString();
   
   setName(moduleName.c_str());


   robotName             = rf.check("robot", 
                           Value("icubSim"), 
                           "Robot name (string)").asString();

   int boardWidth= rf.check("boardWidth", Value(9)).asInt();
   int boardHeight= rf.check("boardHeight", Value(6)).asInt();
   float squaresize= (float) rf.check("boardSize", Value(0.03)).asDouble();

   /* get the name of the input and output ports, automatically prefixing the module name by using getName() */

   inputLeftPortName         = "/";
   inputLeftPortName        += getName(
                           rf.check("imgLeft",Value("/cam/left:i"),"Input image port (string)").asString());
   
   inputRightPortName        = "/";
   inputRightPortName       += getName(
                           rf.check("imgRight", 
                           Value("/cam/right:i"),
                           "Input image port (string)").asString()
                           );
	

   outputPortNameRight        = "/";
   outputPortNameRight       += getName(
                           rf.check("outRight", 
                           Value("/cam/right:o"),
                           "Output image port (string)").asString()
                           );
	
   outputPortNameLeft        = "/";
   outputPortNameLeft       += getName(
                           rf.check("outLeft", 
                           Value("/cam/left:o"),
                           "Output image port (string)").asString()
                           );

   handlerPortName        = "/";
   handlerPortName       += getName(
                           rf.check("CommandPort", 
                           Value("/cmd"),
                           "Output image port (string)").asString()
                           );
    char dirName[255];
    bool proceed=true;


    string dir = rf.getContextPath().c_str();
    for (int i=1; proceed; i++)
        {
           sprintf(dirName,"%s/%s_%.5d",dir.c_str(),"calibImg",i);
		   proceed=!yarp::os::stat(dirName);
           sprintf(dirName,"%s/%s_%.5d/",dir.c_str(),"calibImg",i);
        }
    
    createFullPath(dirName);
    string outoutCalibPath=dirName;
    outoutCalibPath +="/";




    if (!handlerPort.open(handlerPortName.c_str())) {
      cout << ": unable to open port " << handlerPortName << endl;
      return false;
   }
   attach(handlerPort);
   /* create the thread and pass pointers to the module parameters */



   myThread = new stereoCalibThread(inputLeftPortName, inputRightPortName,outputPortNameRight, outputPortNameLeft, &handlerPort,  dirName, boardWidth, boardHeight,squaresize);

   /* now start the thread to do the work */

   myThread->start(); // this calls threadInit() and it if returns true, it then calls run()

   return true ;      // let the RFModule know everything went well
                      // so that it will then run the module
}


bool stereoCalibModule::interruptModule()
{
   myThread->stop();


   return true;
}


bool stereoCalibModule::close()
{

   /* stop the thread */

   myThread->stop();
   delete myThread;

   return true;
}


bool stereoCalibModule::respond(const Bottle& command, Bottle& reply) 
{
  if (command.get(0).asString()=="quit") {
       cout << "me dovrei chiudere.." << endl;
       return false;     
   }
  if (command.get(0).asString()=="s") {
        myThread->setSave();
   }

    if (command.get(0).asString()=="start") {
        myThread->startCalib();
        fprintf(stdout, "Show for 30 times the chess pattern with different orientations and positions \n");
   }
  return true;
}


/* Called periodically every getPeriod() seconds */

bool stereoCalibModule::updateModule()
{
   return true;
}



double stereoCalibModule::getPeriod()
{

    
   return 0.1;
}

void stereoCalibModule::createFullPath(const char* path)
{
	if (yarp::os::stat(path))
    {
        string strPath=string(path);
        size_t found=strPath.find_last_of("/");
    
        while (strPath[found]=='/')
            found--;

        createFullPath(strPath.substr(0,found+1).c_str());
		yarp::os::mkdir(strPath.c_str());
    }
}