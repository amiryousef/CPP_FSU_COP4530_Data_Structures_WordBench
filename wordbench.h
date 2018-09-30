/*
	Amir Yousef - ay10d - yousef
	homework 3 - COP4530 - Spring 12
    wordbench.h
    03/04/12
*/

#ifndef _WORDBENCH_H
#define _WORDBENCH_H

#include <olist.h>
#include <list.h>
#include <pair.h>
#include <compare.h>
#include <xstring.h>

class WordBench
{
public:
  WordBench();
  ~WordBench();

  bool ReadText(const fsu::String& infile);
  bool WriteReport(const fsu::String& outfile, unsigned short c1 = 15, unsigned short c2 = 15) const;
  void ShowSummary() const;
  void Erase();

private:
  // the internal class terminology:
  typedef fsu::Pair      < fsu::String, unsigned long >  EntryType;
  typedef fsu::LessThan  < EntryType >                   PredicateType;

  // choose one associative container class for SetType:
  typedef fsu::UOList          < EntryType , PredicateType >      SetType;
  // typedef fsu::MOList          < EntryType , PredicateType >      SetType;
  // typedef fsu::UOVector        < EntryType , PredicateType >      SetType;
  // typedef fsu::MOVector        < EntryType , PredicateType >      SetType;
  // typedef fsu::RBLLT           < EntryType , PredicateType >      SetType;

  // declare the two class variables:
  SetType                    wordset_;
  fsu::List < fsu::String >  infiles_;
};

#endif
