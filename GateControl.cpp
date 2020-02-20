//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<iostream>

#include	"GateControl.hpp"

using namespace std;

//****************************************************************************************
//
//	CONSTANT DEFINITIONS
//
//****************************************************************************************

//****************************************************************************************
//
//	CLASSES, TYPEDEFS AND STRUCTURES
//
//****************************************************************************************

//****************************************************************************************
//
//	PUBLIC DATA
//
//****************************************************************************************
extern	string	gCurrentDate;

extern	string	gCurrentTime;

//****************************************************************************************
//
//	PRIVATE DATA
//
//****************************************************************************************

//****************************************************************************************
//
//	FUNCTION PROTOTYPES
//
//****************************************************************************************





//****************************************************************************************
//
//	GateControl::AccessAllowed
//
//****************************************************************************************
bool	GateControl::AccessAllowed(CardNumber number) {


		AuthorizationIterator it5;
		Transaction person;

		it5 = authorizationMap_.find(number);

		if(it5 == authorizationMap_.end()){
			person.number_ = number;
			person.name_ = "***";
			person.date_ = gCurrentDate;
			person.time_ = gCurrentTime;
			person.accessAllowed_ = false;
			transactionVector_.push_back(person);

      return false;

		} else {
			if(it5->second.startTime_ <= gCurrentTime && it5->second.endTime_ >= gCurrentTime){

				person.number_ = number;
				person.name_ = it5->second.name_;
				person.date_ = gCurrentDate;
				person.time_ = gCurrentTime;
				person.accessAllowed_ = true;


				transactionVector_.push_back(person);

        return true;
			} else {
				person.number_ = number;
				person.name_ = it5->second.name_;
				person.date_ = gCurrentDate;
				person.time_ = gCurrentTime;
				person.accessAllowed_ = false;
				transactionVector_.push_back(person);

        return false;
			}
		}

}

//****************************************************************************************
//
//	GateControl::AddAuthorization
//
//****************************************************************************************
bool	GateControl::AddAuthorization(CardNumber number, const string& name,
									  const string& startTime, const string& endTime)
{
	if(number > 0 && number <= 9999){

		AuthorizationIterator it5;

		it5 = authorizationMap_.find(number);

		if(it5 != authorizationMap_.end()){
			return false;
		} else {
			Authorization a1;
			a1.number_ = number;
			a1.name_ = name;
			a1.startTime_ = startTime;
			a1.endTime_ = endTime;

			authorizationMap_.insert({number, a1});

      return true;
		}
	}
  return false;
}
//****************************************************************************************
//
//	GateControl::ChangeAuthorization
//
//****************************************************************************************
bool GateControl::ChangeAuthorization(CardNumber number, const string& name,
										 const string& startTime, const string& endTime)
{
	//************************************************************************************
	//	LOCAL DATA
						//find authorization in map
						// overwrite information
						//return true if
	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	if(number > 0 && number <= 9999){
		AuthorizationIterator it5;

		it5 = authorizationMap_.find(number);
		if(it5 != authorizationMap_.end()){
			it5->second.number_ = number;
			it5->second.name_ = name;
			it5->second.startTime_ = startTime;
			it5->second.endTime_ = endTime;
			return true;
		} else {
			return false;
		}
	}
	return false;
}

//*************************************************************************
//
//	GateControl::DeleteAuthorization
//
//****************************************************************************************
bool	GateControl::DeleteAuthorization(CardNumber number) {
	if(number > 0 && number <= 9999){

		AuthorizationIterator it5;

		it5 = authorizationMap_.find(number);
		if(it5 != authorizationMap_.end()){
			authorizationMap_.erase(it5);
      return true;
		} else {
			return false;
		}
	}
  return false;
}

//****************************************************************************************
//
//	GateControl::GetAllAuthorizations
//
//****************************************************************************************
void	GateControl::GetAllAuthorizations(AuthorizationVector& authorizationVector) {
	//************************************************************************************
	//	LOCAL DATA
	//if map is empty, return vector == .clear
	//inorder traversal of the map,

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	if(authorizationMap_.empty()){
		authorizationVector.clear();
	} else {
    authorizationVector.clear();
		for(AuthorizationIterator it5 = authorizationMap_.begin(); it5 != authorizationMap_.end(); it5++){
			authorizationVector.push_back(it5->second);
		}
	}
	return;
}

//****************************************************************************************
//
//	GateControl::GetAllTransactions
//
//****************************************************************************************
void	GateControl::GetAllTransactions(TransactionVector& transactionVector) {
	if(transactionVector_.empty()){
		transactionVector.clear();
	} else {
    transactionVector.clear();
		for(int i = 0; i < transactionVector_.size(); i++){
			transactionVector.push_back(transactionVector_[i]);
		}
	}
	return;
}

//****************************************************************************************
//
//	GateControl::GetCardAuthorization
//
//****************************************************************************************
bool GateControl::GetCardAuthorization(CardNumber number, Authorization& authorization){

	AuthorizationIterator it5;
	it5 = authorizationMap_.find(number);

	if(it5 != authorizationMap_.end()) {
		authorization.number_ = it5->second.number_;
		authorization.name_ = it5->second.name_;
		authorization.startTime_ = it5->second.startTime_;
		authorization.endTime_ = it5->second.endTime_;
		return true;
	} else {
		return false;
	}
}






//****************************************************************************************
//
//	GateControl::GetCardTransactions
//
//****************************************************************************************
bool	GateControl::GetCardTransactions(CardNumber number, TransactionVector& transactionVector) {


		if(transactionVector_.empty()){
			transactionVector.clear();
			return false;
		} else {
			for(int i = 0; i < transactionVector_.size(); i++){
        if(transactionVector_[i].number_ == number)
          transactionVector.push_back(transactionVector_[i]);
      }
        return true;
		}



}
