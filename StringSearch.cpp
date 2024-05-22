// Sequenzierung ATGC

#include <iostream>
#include <random>
#include <fstream>
#include <string>

#define LINES 2000000
#define FILE "file.txt"

using namespace std;

/**
 * Counts the number of occurrences of a substring in a file.
 *
 * @param filename The name of the file to search in.
 * @param substring The substring to search for.
 * @return The number of occurrences of the substring in the file.
 * @throws std::runtime_error if the file cannot be opened.
 */
int countSubstringOccurrences(const string &filename, const string &substring)
{
  ifstream file(filename);
  if (!file)
  {
    throw runtime_error("Could not open file");
  }

  int count = 0;
  string line;
  while (getline(file, line))
  {
    size_t pos = 0;
    while ((pos = line.find(substring, pos)) != std::string::npos)
    {
      ++count;
      pos += substring.length();
    }
  }

  return count;
}

/**
 * Generates a random DNA sequence of the specified length.
 *
 * @param length The length of the DNA sequence to generate.
 * @return The randomly generated DNA sequence.
 */
string generateRandomDNASequence(int length)
{
  static const char alphabet[] = {'A', 'T', 'G', 'C'};
  static default_random_engine rng(random_device{}());
  static uniform_int_distribution<int> distribution(0, sizeof(alphabet) - 2);

  string result;
  result.reserve(length);

  for (int i = 0; i < length; ++i)
  {
    result.push_back(alphabet[distribution(rng)]);
  }

  return result;
}

/**
 * @brief The main function of the program.
 * 
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char *argv[])
{
  string filename = FILE;
  if (argc > 1)
  {
    string arg = argv[1];

    if (arg == "read")
    {
      string substring = "ATG";
      int count = countSubstringOccurrences(filename, substring);
      cout << "The substring " << substring << " occurs " << count << " times in the file " << filename << endl;
    }
    else if (arg == "create")
    {
      ofstream file(filename);
      for (int i = 0; i < LINES; ++i)
      {
        file << generateRandomDNASequence(170) << "\n";
      }
    }
    else
    {
      cout << "Unknown argument" << endl;
      cout << "Usage: " << argv[0] << " [read|create]" << endl;
    }
  }
  else
  {
    cout << "Please provide an argument" << endl;
  }
  return 0;
}
// Performance: LINES 2000000
//> time ./StringSearch create
//________________________________________________________
//Executed in    1,61 secs    fish           external
//   usr time    1,45 secs  355,00 micros    1,45 secs
//   sys time    0,16 secs  283,00 micros    0,16 secs
//
//> time ./StringSearch read
//The substring ATG occurs 12438879 times in the file test
//________________________________________________________
//Executed in  774,45 millis    fish           external
//   usr time  746,28 millis  424,00 micros  745,86 millis
//   sys time   28,17 millis  253,00 micros   27,92 millis
