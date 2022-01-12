#pragma once


#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

typedef size_t CardNumber;

typedef size_t GateNumber;



struct Authorization
{
	Authorization() { }
	
	Authorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
	: number_(number), name_(name), startTime_(startTime), endTime_(endTime) { }

	CardNumber number_;

	string name_;
	
	string startTime_;
	
	string endTime_;
};

typedef map<CardNumber, Authorization> AuthorizationMap;
typedef	AuthorizationMap::iterator AuthorizationMapIter;

typedef	vector<Authorization> AuthorizationVector;

struct Transaction
{
	Transaction() { }

	Transaction(CardNumber number, const string& name, const string& date, const string& time, bool accessAllowed)
	: number_(number), name_(name), date_(date), time_(time), accessAllowed_(accessAllowed) { }

	CardNumber number_;
	
	string name_;
	
	string date_;

	string time_;
	
	bool accessAllowed_;
};

typedef	vector<Transaction> TransactionVector;
typedef	TransactionVector::iterator TransactionVectorIterator;

class	GateControl
{
	public:
		bool accessAllowed(CardNumber number);
	
		bool addAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime);
		
		bool changeAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime);
		
		bool deleteAuthorization(CardNumber number);
		
		void getAllAuthorizations(AuthorizationVector& authorizationVector);
		
		void getAllTransactions(TransactionVector& transactionVector);
	
		bool getCardAuthorization(CardNumber number, Authorization& authorization);

		void getCardTransactions(CardNumber number, TransactionVector& transactionVector);

	private:
		AuthorizationMap authorizationMap_;
		
		TransactionVector transactionVector_;
};



extern string gCurrentDate;

extern string gCurrentTime;



//****************************************************************************************
//
//	TO DO
//
//****************************************************************************************


bool GateControl::accessAllowed(CardNumber number)
{
	
    AuthorizationMapIter it = authorizationMap_.find(number);
     if (it != authorizationMap_.end()){
    transactionVector_.push_back(Transaction(number,it->second.name_,gCurrentDate, gCurrentTime, true));
    return true;
    }
    else {
    transactionVector_.push_back(Transaction(number,it->second.name_,gCurrentDate,gCurrentTime, false));
       return false;
    }

}


bool GateControl::addAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
{
	
	return authorizationMap_.emplace(std::pair<CardNumber,Authorization>(number, Authorization(number, name, startTime,endTime))).second;


}


bool GateControl::changeAuthorization(CardNumber number, const string& name, const string& startTime, const string& endTime)
{
	
    AuthorizationMapIter it = authorizationMap_.find(number);
       if (it != authorizationMap_.end()){
       it->second.name_ = name;
       it->second.startTime_ = startTime;
       it->second.endTime_ = endTime;
       return true;
    }
    return false;
}


bool GateControl::deleteAuthorization(CardNumber number)
{
	
	AuthorizationMapIter it = authorizationMap_.find(number);
       if (it != authorizationMap_.end()){
       authorizationMap_.erase(it);
       return true;

    }
    return false;

}


void GateControl::getAllAuthorizations(AuthorizationVector& authorizationVector)
{
	
	authorizationVector.clear();
    if (!authorizationMap_.empty()){
     for(AuthorizationMapIter it = authorizationMap_.begin(); it != authorizationMap_.end(); it++){
     authorizationVector.push_back(it->second);
     }

    }

}


void GateControl::getAllTransactions(TransactionVector& transactionVector)
{
	
	if (!transactionVector_.empty()){
       transactionVector.assign(transactionVector_.begin(), transactionVector_.end());

    }
    else{
    transactionVector.clear();
    }

}


bool GateControl::getCardAuthorization(CardNumber number, Authorization& authorization)
{

	AuthorizationMapIter it = authorizationMap_.find(number);
    if (it != authorizationMap_.end()){
     authorization.number_ = number;
     authorization.name_ = it->second.name_;
     authorization.startTime_ = it->second.startTime_;
     authorization.endTime_ = it->second.endTime_;
     return true;

    }
    else{
    return false;
    }

}


void GateControl::getCardTransactions(CardNumber number, TransactionVector& transactionVector)
{
	
	if (!transactionVector_.empty()){
     for(TransactionVectorIterator it = transactionVector_.begin();it <= transactionVector_.end(); it++){
     if (it->number_ == number){
     transactionVector.push_back(*it);
     }
     }
    }
    else{
    transactionVector.clear();
    }

}
