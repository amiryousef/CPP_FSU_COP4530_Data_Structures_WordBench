/*
	Amir Yousef - ay10d - yousef
	homework 3 - COP4530 - Spring 12
    wordbench.cpp
    03/04/12
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <wordbench.h>

WordBench::WordBench()
{}

WordBench::~WordBench()
{
  Erase();
}

bool WordBench::ReadText(const fsu::String& infile)
{
  std::ifstream ifs;
  unsigned long wordcount = 0;
  char c;

  // open file
  ifs.open(infile.Cstr());

  // if could not open file
  if (!ifs)
    return false;

  // get the character
  c = ifs.get();

  // while character is not end of file
  while (c != EOF)
  {
    fsu::String word;

    while (c != EOF && 
      (c < 'a' || c > 'z') && (c < 'A' || c > 'Z') &&
      (c < '0' || c > '9') && 
      (c != '-'))
    {
      c = ifs.get();
    }

    while (c != EOF && 
      ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
      (c >= '0' && c <= '9') || 
      (c == '-') || (c == '\'')))
    {
      if (c == '\'' && ifs.peek() == '\'')
      {
        c = ifs.get();
        break;
      }

      // convert character to lowercase
      if (c >= 'A' && c <= 'Z')
        c = 'a' + (c - 'A');

      word = word + fsu::String(1, c);
      c = ifs.get();
    }

    if (word.Length() > 0 && word[word.Length() - 1] == '\'')
      word[word.Length() - 1] = '\0';

    if (word.Length() > 0)
    {
      EntryType entry(word);
      SetType::Iterator iter = wordset_.Includes(entry);

      if (iter == wordset_.End())
        entry.second_ = 1;
      else
        entry.second_ = (*iter).second_ + 1;

      wordset_.Insert(entry);
      wordcount++;
    }
  }

  // close file
  ifs.close();

  // add file name into list
  infiles_.PushBack(infile);

  std::cout << "\n     Number of words read:    " << wordcount;
  std::cout << "\n     Current vocabulary size: " << wordset_.Size();
  std::cout << '\n';

  return true;
}

bool WordBench::WriteReport(const fsu::String& outfile, unsigned short c1, unsigned short c2) const
{
  std::ofstream ofs;
  fsu::List < fsu::String >::ConstIterator fileIter;
  SetType::ConstIterator wordIter;
  unsigned long wordcount = 0;

  // open file
  ofs.open(outfile.Cstr());

  // if could not open file
  if (!ofs)
    return false;

  ofs << "Text Analysis for files:";
  
  fileIter = infiles_.Begin();

  while (fileIter != infiles_.End())
  {
    if (fileIter != infiles_.Begin())
      ofs << ",";

    ofs << " " << (*fileIter);
    ++fileIter;
  }

  ofs << "\n\n";
  ofs << std::left << std::setw(c1) << "word";
  ofs << std::right << std::setw(c2) << "frequency";
  ofs << '\n';
  ofs << std::left << std::setw(c1) << "----";
  ofs << std::right << std::setw(c2) << "---------";
  ofs << '\n';

  wordIter = wordset_.Begin();

  while (wordIter != wordset_.End())
  {
    ofs << std::left << std::setw(c1) << (*wordIter).first_;
    ofs << std::right << std::setw(c2) << (*wordIter).second_;
    ofs << '\n';
    wordcount += (*wordIter).second_;
    ++wordIter;
  }

  ofs << "\nNumber of words: " << wordcount;
  ofs << "\nVocabulary size: " << wordset_.Size();
  ofs << '\n';

  // close file
  ofs.close();

  std::cout << "\n     Number of words:         " << wordcount;
  std::cout << "\n     Vocabulary size:         " << wordset_.Size();
  std::cout << "\n     Analysis written to file " << outfile;
  std::cout << '\n';

  return true;
}

void WordBench::ShowSummary() const
{
  fsu::List < fsu::String >::ConstIterator fileIter = infiles_.Begin();
  SetType::ConstIterator wordIter;
  unsigned long wordcount = 0;

  std::cout << "\n     Current files:           ";
  
  if (fileIter != infiles_.End())
  {
    std::cout << (*fileIter);
    ++fileIter;
  }

  while (fileIter != infiles_.End())
  {
    std::cout << ", " << (*fileIter);
    ++fileIter;
  }

  wordIter = wordset_.Begin();

  while (wordIter != wordset_.End())
  {
    wordcount += (*wordIter).second_;
    ++wordIter;
  }

  std::cout << "\n     Current word count:      " << wordcount;
  std::cout << "\n     Current vocabulary size: " << wordset_.Size();
  std::cout << '\n';
}

void WordBench::Erase()
{
  wordset_.Clear();
  infiles_.Clear();
}
