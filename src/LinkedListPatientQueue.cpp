
#include "LinkedListPatientQueue.h"
#include <error.h>
#include "strlib.h"
#include <cstddef>

LinkedListPatientQueue::LinkedListPatientQueue() {
    front=NULL;
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    clear();
    delete front;
}

void LinkedListPatientQueue::clear() {
    PatientNode* cp = front;
    PatientNode* next=front;
    while(next!=NULL){
        next=cp->next;
        delete cp;
        cp=next;
    }
    front=NULL;
}

string LinkedListPatientQueue::frontName() {
    string name;
    if (front==NULL){
        name="";
        throw ErrorException("The patient queue is empty!");
    }else{
        name=front->name;
    }
    return name;
}

int LinkedListPatientQueue::frontPriority() {
    int priority;
    if (front==NULL){
        priority=-1;
        throw ErrorException("The patient queue is empty!");
    }else{
        priority=front->priority;
    }
    return priority;
}

bool LinkedListPatientQueue::isEmpty() {
    return (front==NULL);
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    if(front==NULL){
        front = new PatientNode(name,priority,NULL);
    }else{
        PatientNode* newNode;
        if(priority < front->priority){
            newNode=front;
            front= new PatientNode(name,priority,newNode);
        }else{
            for( PatientNode* current=front;current!=NULL;current=current->next){
                if(current->next==NULL ){
                    newNode=new PatientNode(name,priority,current->next);
                    current->next=newNode;
                    break;
                }else if(priority < current->next->priority){
                    newNode=new PatientNode(name,priority,current->next);
                    current->next=newNode;
                    break;
                }
            }
        }
    }
    return;
}

string LinkedListPatientQueue::processPatient() {
    string name="";
    if(front==NULL){
        throw ErrorException("The patient queue is empty!");
    }else{
        PatientNode* node=front->next;
        name=front->name;
        delete front;
        front=node;
    }
    return name;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    if (front==NULL){
        throw ErrorException("The patient queue is empty!");
    }else{
        PatientNode* node=NULL;
        PatientNode* beforeNode=NULL;
        PatientNode* previous=front;
        for(PatientNode* pn=front;pn!=NULL;pn=pn->next){
            if(pn->name==name && pn->priority>newPriority){
                if(node==NULL){
                    node=pn;
                    beforeNode=previous;
                }else if(pn->priority > node->priority){
                    node=pn;
                    beforeNode=previous;
                }
                if(pn!=front){
                    previous=pn;
                }
            }
        }
        if(node==NULL){
            throw ErrorException("The patient has a more urgent priority than the given new priority"
                                 " or given patient is not in the queue!");
        }else{
            beforeNode->next=node->next;
            delete node;
            newPatient(name,newPriority);
        }
    }
    return;
}

string LinkedListPatientQueue::toString() {
    string output="{";
    if(!front==NULL){
        for(PatientNode* pn=front;pn!=NULL;pn=pn->next){
            output+=(integerToString(pn->priority)+":"+pn->name+", ");
        }
        output.erase(output.end()-2,output.end());
    }
    output+="}";
    return output;
}
