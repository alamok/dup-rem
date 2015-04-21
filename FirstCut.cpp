#include<iostream>
// #include<algorithm>
#include<iterator>
#include<sstream>
#include<boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

int total_files;

int printPaths( path p, int level, std::vector<std::string> & paths, std::vector<std::string> & fileNames )
{
  level++;
    if (exists(p))    // does p actually exist?
    {
      if (is_regular_file(p))        // is p a regular file?
        cout << p << " size is " << file_size(p) << '\n';

      else if (is_directory(p))      // is p a directory?
      {
	for( directory_iterator itr(p) ; itr != directory_iterator(); itr++)
	  {
	    for(int index = 0 ; index < level ; ++index )
	      cout << "--";
	    //cout << itr->path() << endl;
	    std::stringstream currentStream;
	    currentStream << itr->path() ;
	    std::string current = currentStream.str();
	    cout << current << endl;
	    paths.push_back( current );
	    std::string toFind = "/";
            size_t pos = current.find_last_of( toFind, current.size() );
	    std::string currentFileName( current, pos + 1 , current.size() );
	    fileNames.push_back( currentFileName );
	    //cout << fileNames << endl;
	    //cout << pos << endl;
	    path current_p(itr->path());
	    file_status currentDirStatur = symlink_status( current_p );
	    if( is_directory(current_p) && !is_symlink( currentDirStatur ) )
	      {
		printPaths( current_p, level, paths, fileNames );
	      }
	    total_files++;
	  }
   }
      else
        cout << p << " exists, but is neither a regular file nor a directory\n";
    }
    else
      cout << p << " does not exist\n";
}


int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    cout << "Usage: tut3 path\n";
    return 1;
  }

  total_files = 0;

  path p (argv[1]);   // p reads clearer than argv[1] in the following code
  int level = 0;
  
  // call funciton compute files inside
  try
  {
    std::vector<std::string> paths;
    std::vector<std::string> fileName;

    int level = 0 ;
    printPaths( p , level, paths, fileName );
    cout << "Total " << total_files << " files and directories found in the root " << endl;

    for( int i =0 ; i < fileName.size() -1 ; i++ )
      {
	for( int j = i+1; j < fileName.size(); j++ )
	  {
	    if( fileName[j].size() > fileName[i].size() )
	      {
		std::string::size_type n;
	        // the additional " might mess this up!
		n = fileName[j].find( fileName[i]);
		if (n != std::string::npos) 
		{
		  // ?? still left 
		}
	
	      }

	  }
      }
  }

  catch (const filesystem_error& ex)
  {
    cout << ex.what() << '\n';
  }
  return 0;
}


/* g++ -o FirstCut FirstCut.cpp -L /usr/local/lib -lboost_filesystem -lboost_system */
