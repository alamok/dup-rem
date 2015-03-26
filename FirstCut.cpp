#include<iostream>
// #include<algorithm>
#include<iterator>
#include<boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

int total_files;

int printPaths( path p, int level )
{
  level++;
    if (exists(p))    // does p actually exist?
    {
      if (is_regular_file(p))        // is p a regular file?
        cout << p << " size is " << file_size(p) << '\n';

      else if (is_directory(p))      // is p a directory?
      {
        // cout << p << " is a directory containing:\n";

	/*

        copy(directory_iterator(p), directory_iterator(),  // directory_iterator::value_type
          ostream_iterator<directory_entry>(cout, "\n"));  // is directory_entry, which is
	                                                   // converted to a path by the
                                                           // path stream inserter

							   */
	for( directory_iterator itr(p) ; itr != directory_iterator(); itr++)
	  {
	    for(int index = 0 ; index < level ; ++index )
	      cout << "--";
	    cout << itr->path() << endl;
	    path current_p(itr->path());
	    file_status currentDirStatur = symlink_status( current_p );
	    if( is_directory(current_p) && !is_symlink( currentDirStatur ) )
	      {
		printPaths( current_p, level );
	      }
	    total_files++;
	  }


	//cout << "printing from my new function" << endl;
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
    int level = 0 ;
    printPaths( p , level );
    cout << "Total " << total_files << " files and directories found in the root " << endl;
    /*


    if (exists(p))    // does p actually exist?
    {
      if (is_regular_file(p))        // is p a regular file?
        cout << p << " size is " << file_size(p) << '\n';

      else if (is_directory(p))      // is p a directory?
      {
        cout << p << " is a directory containing:\n";

        copy(directory_iterator(p), directory_iterator(),  // directory_iterator::value_type
          ostream_iterator<directory_entry>(cout, "\n"));  // is directory_entry, which is
                                                           // converted to a path by the
                                                           // path stream inserter
      }
      else
        cout << p << " exists, but is neither a regular file nor a directory\n";
    }
    else
      cout << p << " does not exist\n";
    */
  }

  catch (const filesystem_error& ex)
  {
    cout << ex.what() << '\n';
  }

  return 0;
}


/* g++ -o FirstCut FirstCut.cpp -L /usr/local/lib -lboost_filesystem -lboost_system */
