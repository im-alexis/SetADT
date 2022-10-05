// Set <Project5.cpp>
// EE 312 Project 5 submission by
// Alexis Torres
// at39625
// Slip days used: 0
// Spring 2022

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */

int cmpInt (const void *num1, const void *num2){ // for  a quick sort in the c library
    return (*(int*)num1 - *(int*)num2);
}

int binSea(int* arr,int firstIndex, int len, int x) { // looks through the array and returns the index of the number z
   if(arr != NULL) {// array can't be null
       if(arr[firstIndex]<=x) { // x has to be greater than the first number to be in the array, since its sorted
           if (x <= arr[len - 1]) {
               int mid = (len + firstIndex) / 2;
               if (arr[mid] == x) {
                   return mid;
               }
               if (x > arr[mid]) {
                   return binSea(arr, mid + 1, len, x);
               }
               if (x < arr[mid]) {
                   return binSea(arr, firstIndex, mid, x);
               }
           }
       }
   }
    return -1;
}



/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }
    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    if (isEmptySet(self)){//if self is empty then x is not a member
        return false;
    }
    if(binSea(self->elements,0, self->len,x) != -1) { //Simply search with the binary search if its there then its a memeber
        return true;
    }
    return false; // anything else happens then naw
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {

    if (isMemberSet(self, x) == false){
        self->len = self->len +1;
        self->elements = (int*) realloc(self->elements, (sizeof(int) * (self->len))); //increase the size of the block by 1 int to add the number
        self ->elements[self ->len -1] = x; //adds at then end
        qsort(self->elements,self->len, sizeof (int), cmpInt);// sorts the array since x is added without a care at the end
    }
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    if (isEmptySet(self)){
        return;
    }
    int k = binSea(self->elements, 0 , self->len,x);
    if(k != -1){
        //int k = binSea(self->elements, 0 , self->len,x);
        for(k=k; k<self->len-1; k++){
            self->elements[k] = self->elements[k+1];

              }
        self->len --;
    }
    if(self->len == 0){
        free(self->elements);
        self->elements = nullptr;
    }

}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if (self->len != other->len){ // if the lengths arent equal return false
        return false;
    }
    int i;
    for(i=0; i<self->len; i++){
        if(self->elements[i] != other->elements[i]){// if at any point the elements arent equal return false
            return false;
        }
    }
    return true; // return true any other time
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    if (isEmptySet(self)) {                 //if self is empty then it will always be subset
        return true;
    }
    if (self->len > other->len){       //if self len is bigger then can't be a subset
        return false;
    }

    int j=0;
    for(int i=0; i<self->len; i++){
        if(j>=other->len){
            return false;
        }
        if(self->elements[i]==other->elements[j]){
            j++;
        }
        else if(self->elements[i] < other->elements[j]){  //if the jth element of other is bigger than self then every element of self isn't an element of other
            return false;
        }
        else{             //in this case only increment the j index and keep i index the same
            j++;
            i--;
        }
    }
    return true;

}


/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other){
    if (self->len == 0){  //if length is 0 then function does nothing
        return;
    }
    if(isEqualToSet(self,other)){ //if they are equal then no elements need to be removed
        return;
    }
    int* tmpHold = (int*)malloc(sizeof(int)*self->len);//to temporary hold the numbers

    if (isEmptySet(other)){
        free(self->elements);
        self->elements = tmpHold;
        self->len = 0;
        return;
    }
    int i;//moving through the self array
    int j=0;// moving through the other array
    int inIndex=0; // keep track of where in the tmp array
    int inLen=0;

    for(i=0; i<self->len; i++){
       if(j >= other->len){  //means you have gone through all elements in other so stop looping
            break;
        }
        else{

            if (self->elements[i] == other->elements[j]) {      //we got a match
                tmpHold[inIndex] = self->elements[i];        //save one of the elements into the tmp
                j++;//increase the counters
                inIndex++; // move to the next spot
                inLen++;

            }
            else if (self->elements[i] > other->elements[j]) {    //in this case only increment the other and i the same
                i--;
                j++;            //keep searching for intersection
            }
            else{   //only reach this if jth element of other is bigger than ith element of self, in this case do nothing
                continue;
            }
        }
    }
    free(self->elements);
    self->elements = tmpHold;
    self->len = inLen;

}

/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other)
{
    int* tmpHold2 = (int*)malloc(sizeof(int)*(self->len));//tmp holding for elements being sub
    int sIndex =0;
    int sLen=0;

    if (isEmptySet(self)){
        free(tmpHold2);//if self empty do nothing
        return;
    }
    if(isEmptySet(other)){
        free(tmpHold2); // if self empty do nothing
        return;
    }

    int i=0;// index tracker (self)
    int j=0;// index tracker (other)

    while(i < self->len){
        if(j>=other->len){   //copy the element and increment index
            tmpHold2[sIndex]=self->elements[i];    //copy rest of elements
            i++;
            sIndex++;
            sLen++;
        }
        else{
            if (self->elements[i] < other->elements[j]) {        //if the element of self is less than other than copy element and increase index
                tmpHold2[sIndex] = self->elements[i];
                i++;
                sIndex++;
                sLen++;
            }
            else if (self->elements[i] > other->elements[j]){        //only increment j index
                j++;
            }
            else {       // they are equal so just increase both
                i++;
                j++;
            }
        }
    }
    free(self->elements); //release it a make tmp the new elements
    self->elements = tmpHold2;
    self->len = sLen;

}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other){
    int* tmpHold3 = (int*)malloc((self->len + other->len) * sizeof(int)); // must be combined size of self and other
    if (isEmptySet(other)){//didn't use it so free
        free(tmpHold3);
        return;
    }
    int i=0;
    int j=0;
    int uIndex=0;
    int uLen=0;

    while(i < other->len){
        if (j < self->len){
            if (other->elements[i] == self->elements[j]){
                tmpHold3[uIndex] = other->elements[i];  //copy the element of other into the tmp
                i++;
                j++;
                uIndex++;
                uLen++;
            }
            else if (other->elements[i] > self->elements[j]){    //can't skip over the jth element of self
                tmpHold3[uIndex] = self->elements[j];
                j++;
                uIndex++;
                uLen++;
            }
            else{  //this means ith element of other is greater than jth element of self
                tmpHold3[uIndex] = other->elements[i]; //copy that element of other
                i++;
                uIndex++;
                uLen++;
            }
        }
        else if(j >= self->len){   //stop increasing j because it reached the end of self
            tmpHold3[uIndex] = other->elements[i]; //copy rest of the elements
            i++;
            uIndex++;
            uLen++;
        }
    }

    if (j < self->len){
        while(j < self->len){
            tmpHold3[uIndex] = self->elements[j];  //copy the rest of the self elements
            j++;
            uIndex++;
            uLen++;
        }
    }
    free(self->elements);
    self->elements = tmpHold3;
    self->len = uLen;


}