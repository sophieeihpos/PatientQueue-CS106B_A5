
#include "VectorPatientQueue.h"
#include "vector.h"
#include <string>

VectorPatientQueue::VectorPatientQueue() {
    queue= new Vector<patient>();
}

VectorPatientQueue::~VectorPatientQueue() {
    delete queue;
}

void VectorPatientQueue::clear() {
    queue->clear();
    count=0;
}

int VectorPatientQueue::findMostUrgent(){
    int index=0;
    int minPriority=queue->get(0).priority;
    if (!queue->isEmpty()){
        for(patient p:*queue){
            if(p.priority==minPriority){
                if(p.index<index){
                    index=p.index;
                }
            }else if(p.priority<minPriority){
                minPriority=p.priority;
                index=p.index;
            }
        }
    }
    return index;

}

string VectorPatientQueue::frontName() {
    if(queue->isEmpty()){
        throw ErrorException("The patient queue is empty!");
        return "";
    }else{
        int index=findMostUrgent();
        patient p=queue->get(index);
        return p.name;
    }
}

int VectorPatientQueue::frontPriority() {
    if(queue->isEmpty()){
        throw ErrorException("The patient queue is empty!");
        return -1;
    }else{
        int index=findMostUrgent();
        patient p=queue->get(index);
        return p.priority;
    }
}

bool VectorPatientQueue::isEmpty() {
    return (count<0);
}

void VectorPatientQueue::newPatient(string name, int priority) {
    patient *p= new patient;
    p->name=name;
    p->priority=priority;
    count++;
    p->index=count;
    queue->add(*p);
}

string VectorPatientQueue::processPatient() {
    string name;
    if(!queue->isEmpty()){
        int index=findMostUrgent();
        if(index<count){
            for(int i=index+1;i<=count;i++){
                patient p=queue->get(i);
                p.index=i-1;
                queue->set(i,p);
            }
        }
        name=queue->get(index).name;
        queue->remove(index);
        count--;
    }else{
        name="";
        throw ErrorException("The patient queue is empty!");
    }
    return name;
}

void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    if(queue->isEmpty()){
        throw ErrorException("The patient queue is empty!");
        return;
    }else{
        int maxPriority=-1;
        int index=0;
        for (patient p:*queue){
            if(p.name==name){
                if(p.priority>newPriority){
                    if(p.priority>maxPriority){
                        maxPriority=p.priority;
                        index=p.index;
                    }
                }
            }
        }
        if(maxPriority==-1){
            throw ErrorException("The patient has a more urgent priority than the given new priority"
                           " or given patient is not in the queue!");
            return;
        }else{
            patient p=queue->get(index);
            p.priority=newPriority;
            queue->set(index,p);
            return;
        }
    }
}

string VectorPatientQueue::toString() {
    string output="{";
    if(!queue->isEmpty()){
        for (patient p:*queue){
            output+=(integerToString(p.priority)+":"+p.name+", ");
        }
        output.erase(output.end()-2,output.end());
    }
    output+="}";
    return output;
}
