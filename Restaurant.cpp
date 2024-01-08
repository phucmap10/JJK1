#include "main.h"
class imp_res : public Restaurant
{
public:
	imp_res(){};
	int sokhach = 0;
	customer *head = nullptr;
	customer *tail = nullptr;
	customer *curr = nullptr;
	customer *headwait = nullptr;
	customer *tailwait = nullptr;
	customer *currwait = nullptr;
	int queuesize = 0;
	customer *orderhead = nullptr;
	customer *ordercurr = nullptr;
	customer *orderwaithead = nullptr;
	customer *orderwaitcurr = nullptr;
	customer *orderwaittail = nullptr;
	void RED(string name, int energy)
	{
		cout << name << " " << energy << endl;
		customer *cus = new customer(name, energy, nullptr, nullptr);
		if (cus->energy == 0)
		{
			return;
		}
		if (sokhach == 0)
		{
			head = cus;
			tail = cus;
			cus->next = cus->prev = cus;
			curr = cus;
			/*orderhead = cus;
			ordercurr = cus;*/
			ordercurr = new customer(cus->name,cus->energy,NULL,NULL);
			ordercurr = orderhead;
			sokhach++;
		}
		else if (sokhach > 0 && sokhach < MAXSIZE / 2)
		{
            int n=0;
			while (n<sokhach)
			{
				if (head->name == cus->name)
				{
					return;
				}
				head = head->next;
                n++;
			}
			if (cus->energy >= curr->energy)
			{

				cus->next = curr->next;
				cus->prev = curr;
                curr->next->prev=cus;
				curr->next = cus;
				curr = cus;
				/*ordercurr->next = cus;
				ordercurr = cus;*/
				ordercurr = new customer(cus->name,cus->energy,NULL,NULL);
				ordercurr=ordercurr->next;
				sokhach++;
			}
			else if (cus->energy < curr->energy)
			{
				cus->next = curr;
				cus->prev = curr->prev;
				curr->prev->next = cus;
				curr->prev = cus;
				curr = cus;
				/*ordercurr->next = cus;
				ordercurr = cus;*/
				ordercurr = new customer(cus->name,cus->energy,NULL,NULL);
				ordercurr=ordercurr->next;
				sokhach++;
			}
		}
		else if (sokhach > 0 && sokhach >= MAXSIZE / 2)
		{	int n = 0;
			int RES =cus->energy- head->energy;
			int RES1 = RES;
			customer *lonnhat=curr;
			customer* chay = head;
			for(int i = 0; i <sokhach; i++){
                RES = abs(cus->energy - chay->energy);
                if(RES1 < RES){
                    RES1 = RES;
                    lonnhat = chay;
                }
                chay=chay->next;
            }
			if (cus->energy-lonnhat->energy < 0)
			{
				cus->next = lonnhat;
				cus->prev = lonnhat->prev;
				lonnhat->prev->next = cus;
				lonnhat->prev = cus;
				curr = cus;
				ordercurr = new customer(cus->name,cus->energy,NULL,NULL);
				ordercurr=ordercurr->next;
				sokhach++;
			}
			if (cus->energy - lonnhat->energy > 0)
			{
				cus->next = lonnhat->next;
				cus->prev = lonnhat;
				lonnhat->next->prev = cus;
				lonnhat->next = cus;
				curr = cus;
				ordercurr = new customer(cus->name,cus->energy,NULL,NULL);
				ordercurr=ordercurr->next;
				sokhach++;
			}
		}
		else if (sokhach == MAXSIZE)
		{
			if (queuesize == 0)
			{
				for (int i = 0; i < sokhach; i++)
				{customer* tmp = head;
					if (tmp->name == cus->name)
					{
						return;
					}
					tmp = tmp->next;
				}
				headwait = cus;
				tailwait = cus;
				cus->next = cus->prev = cus;
				currwait = cus;
				queuesize++;
				orderwaithead = new customer(cus->name,cus->energy,NULL,NULL);
				orderwaithead->next = orderwaithead->prev = orderwaithead;
				orderwaitcurr = orderwaithead;
				orderwaittail = orderwaithead;
			}
			if (queuesize > 0 && queuesize < MAXSIZE)
			{
				for (int i = 0; i < sokhach; i++)
				{	customer* tmp = head;
					if (tmp->name == cus->name)
					{
						return;
					}
					tmp = tmp->next;
				}
				for (int i = 0; i < queuesize; i++)
				{	customer* tmp = headwait;
					if (tmp->name == cus->name)
					{
						return;
					}
					tmp = tmp->next;
				}
				cus->next = currwait->next;
				cus->prev = currwait;
				currwait->next->prev = cus;
				currwait->next = cus;
				currwait = currwait->next;
				customer* orderwaitcurr1 = new customer ( cus->name,cus->energy,NULL, NULL);
				orderwaitcurr1->prev = orderwaitcurr;
				orderwaitcurr->next = orderwaitcurr1;
				orderwaitcurr = orderwaitcurr->next;
				queuesize++;
			}
			
		}
	}
	void BLUE(int num)
	{
		cout << "blue " << num << endl;
		if (num == MAXSIZE || num == sokhach)
		{
			for (int i = 0 ; i < sokhach; i++)
			{
				customer *tmpp = head;
				head->prev->next = head->next;
                head->next->prev = head->prev;
                head = head->next;
                tmpp->next = tmpp->prev = NULL;
				delete tmpp;
			}
			sokhach = 0;
		}
		else if (num < sokhach)
		{
			int n = num;
			customer *temp = head;
			for (int i = 0; i < n; i++)
			{
				if (temp->name == orderhead->name)
				{
					customer *tmp = temp;
					tmp->prev->next = tmp->next;
					tmp->next->prev = tmp->prev;
                    tmp->next = tmp->prev = NULL;
                    temp = temp->next;
					delete tmp;
					customer *xoa = orderhead;
					orderhead = orderhead->next;
					delete xoa;
                    sokhach--;
				}
				else temp = temp->next;
				
				
			}
			customer *currentNodeAfterRemove = temp;
			if (temp->energy > 0)
			{
				currentNodeAfterRemove = temp->next;
			}
			else
			{
				currentNodeAfterRemove = temp->prev;
			}
			curr = currentNodeAfterRemove;
			delete temp;
		}
		// can dieu chinh lai curr toi vi tri vua xoa
		customer *currentNodeAfterRemove = curr;
		if (curr->energy > 0)
		{
			currentNodeAfterRemove = curr->next;
		}
		else
		{
			currentNodeAfterRemove = curr->prev;
		}
		if (sokhach == 1)
		{
			currentNodeAfterRemove = NULL;
		}
		curr = currentNodeAfterRemove;
		while (headwait != NULL && sokhach < MAXSIZE)
		{
			customer *vaoban;
			vaoban = headwait;
			RED(headwait->name, headwait->energy);
			headwait = headwait->next;
			delete vaoban;
			queuesize--;
		}
	}
	void swapData(customer* a, customer* b){
		string tmp;
		int temp;
		tmp = a->name;
		temp = a->energy;
		a->name = b->name;
		a->energy = b->energy;
		b->name = tmp;
		b->energy = temp;
	}
	void PURPLE()
	{
		cout << "purple" << endl;
		int n = queuesize;
		int maxenergy = 0;
		if(tailwait == NULL || tailwait->next == tailwait)
		{
			return;
		}
		customer* maxnode = NULL;
		customer* p =tailwait->next;
		do{
			if(abs(p->energy) >= maxenergy){
				maxenergy = abs(p->energy); // neu tri tuyet doi > max e thi cap nhat max e
				maxnode = p;
			}
			p = p->next;
		}while(p!=tail->next);
		int gap = n/2;
		int count = 0; // bien dem so lan chuyen vi tri
		while(gap > 0){
			p = maxnode;
			for(int i = 0; i < gap; i++){
				customer* q = p;
				while(q!= tail){
					customer* r = q;
					for(int j = i + gap; j < n; j+= gap ){
						r = r->next;
						if(q->energy < r->energy || q->energy == r->energy && q->name > r->name){
							swapData(q,r);
							count++;
						}//neu du lieu cua q < r thi swap
					}
					q = q->next;
				}
				p = p->next;
			}
			gap = gap/2;
			 // duyet qua phan tu theo khoang cach gap

		}
		BLUE(count % MAXSIZE);
	}
	void REVERSAL()
	{
		cout << "reversal" << endl;
        string name=curr->name;
		customer *chuthuat = NULL;
		customer *chulinh = NULL;
		customer *markchuthuat = NULL;
		customer *markchulinh = NULL;
		for (int i = 0; i < sokhach; i++)
		{
			if (curr->energy > 0)
			{
				if (chuthuat == NULL)
				{
					chuthuat = new customer(curr->name, curr->energy, nullptr, nullptr);
					markchuthuat = chuthuat;
				}
				else
				{
					chuthuat->next = new customer(curr->name, curr->energy, nullptr, nullptr);
					chuthuat = chuthuat->next;
				}
			}
			else if (curr->energy < 0)
			{
				if (chulinh == NULL)
				{
					chulinh = new customer(curr->name, curr->energy, nullptr, nullptr);
					markchulinh = chulinh;
				}
				else
				{
					chulinh->next = new customer(curr->name, curr->energy, nullptr, nullptr);
					chulinh = chulinh->next;
				}
			}
			curr = curr->prev;
		}
        curr=curr->next;
        customer* tmp=nullptr;
		for (int i = 0; i < sokhach; i++)
		{
			if (curr->energy > 0)
			{
				/*curr = markchuthuat;
				customer *tmp = markchuthuat;
				if (markchuthuat->next != NULL)
				{
					markchuthuat = markchuthuat->next;
				}
				delete tmp;*/
                curr->energy=markchuthuat->energy;
                curr->name = markchuthuat->name;
                markchuthuat = markchuthuat->next;
			}
			else
			{
				curr->energy = markchulinh->energy;
                curr->name = markchulinh->name;
                markchulinh = markchulinh->next;
			}
            if(curr->name==name)tmp=curr;
            curr = curr->next;
		}
        curr=tmp;
		
	}
	void UNLIMITED_VOID()
	{
		cout << "unlimited_void" << endl;
		customer *start = NULL;
		customer *end = NULL;
		int min_sum = curr->energy;
		int current_sum = curr->energy;
		int current_length = 1;
		int max_length = 1;
		customer *current_node = curr->next;
		while (current_node != curr)
		{
			current_sum += current_node->energy;
			current_length++;

			if (current_sum < min_sum)
			{
				min_sum = current_sum;
				start = current_node;
				end = current_node;
			}
			if (current_length >= 4 && current_sum == min_sum)
			{
				end = current_node;
			}
			if (current_sum > 0)
			{
				current_sum = 0;
				current_length = 0;
			}
			current_node = current_node->next;
		}
		int count = 0;
		while (start->next != end->next)
		{
			count++;
			start = start->next;
		}
		customer *daycon = NULL;
		customer *luutru = NULL;
		for (int i = 0; i < count; i++)
		{
			if (daycon == NULL)
			{
				daycon = new customer(start->name, start->energy, start->prev, start->next);
				daycon->next = daycon->prev = daycon;
				luutru = daycon;
			}
			else
			{
				daycon = new customer(start->name, start->energy, start->prev, start->next);
				luutru->next = daycon;
				luutru->next->prev = luutru;
				luutru->prev = daycon->next;
				luutru = luutru->next;
			}
		}
		customer *tmp = NULL;
		int min_e = 9999999;
		while (luutru->next != luutru)
		{
			if (luutru->energy < min_e)
			{
				min_e = luutru->energy;
				tmp = luutru;
			}
			luutru = luutru->next;
		}

		while (luutru->next != luutru)
		{
			cout << luutru->name << "-" << luutru->energy;
		}

		while (daycon->next != NULL)
		{
			customer *tmp = daycon;
			daycon = daycon->next;
			delete tmp;
		}
		while (luutru->next != NULL)
		{
			customer *tmp = luutru;
			luutru = luutru->next;
			delete tmp;
		}
	}
	void DOMAIN_EXPANSION()
	{
		cout << "domain_expansion" << endl;
		long long chuthuat = 0;
		long long chulinh = 0;
		while (head->next != head)
		{
			if (head->energy > 0)
			{
				chuthuat = chuthuat + head->energy;
			}
			else if (head->energy < 0)
			{
				chulinh = chulinh + head->energy;
			}
			head = head->next;
		}
		while (headwait->next != headwait)
		{
			if (headwait->energy > 0)
			{
				chuthuat = chuthuat + headwait->energy;
			}
			else if (headwait->energy < 0)
			{
				chulinh = chulinh + headwait->energy;
			}
			headwait = headwait->next;
		}
		customer *dungdexoa = orderhead;
		customer *tmp = orderhead;
		dungdexoa->next->prev = dungdexoa;
		tmp = tmp->next;
		while (tmp->next != NULL)
		{
			dungdexoa->next = tmp;
			dungdexoa->next->prev = dungdexoa;
			dungdexoa->prev = dungdexoa->next;
			dungdexoa = dungdexoa->next;
		}
		tmp = tmp->next;
		delete tmp;

		customer *removepos = NULL;

		if (chuthuat > abs(chulinh))
		{	customer* track = orderwaittail;
			while (track->prev != orderwaittail)
			{
				while (track->energy > 0)
				{
					track = track->prev;
				}
				customer *tmp = track;
					if (tmp->energy < 0)
					{
						customer *temp = tmp;
						tmp->prev->next = tmp->next;
						tmp->next->prev = tmp->prev;
						tmp = tmp->prev;
						delete temp;
					}
			}
			while (dungdexoa->prev != dungdexoa)
			{
				while (dungdexoa->energy > 0)
				{
					dungdexoa = dungdexoa->prev;
				}
				customer *tmp = head;
				while (tmp->next != head)
				{
					if (tmp->name == dungdexoa->name && tmp->energy == dungdexoa->energy)
					{
						cout << dungdexoa->name << "-" << dungdexoa->energy;
						tmp->prev->next = tmp->next;
						tmp->next->prev = tmp->prev;
					}
					tmp = tmp->next;
					if (tmp->energy > 0)
					{
						removepos = tmp->next;
					}
					else
					{
						removepos = tmp->prev;
					}
				}
				curr = removepos;
			}

			while (orderhead->next != NULL)
			{
				if (orderhead->energy < 0)
				{
					customer *tmp = orderhead;
					orderhead = orderhead->next;
					delete tmp;
				}
				orderhead = orderhead->next;
			}
		}
		else if (chuthuat < abs(chulinh))
		{
			customer *track = orderwaittail;
			while (track->prev != orderwaittail)
			{
				while (track->energy < 0)
				{
					track = track->prev;
				}
				customer *tmp = track;
				if (tmp->energy > 0)
				{
					customer *temp = tmp;
					tmp->prev->next = tmp->next;
					tmp->next->prev = tmp->prev;
					tmp = tmp->prev;
					delete temp;
				}
				track = track->prev;
			}
			while (dungdexoa->energy < 0)
			{
				dungdexoa = dungdexoa->prev;
			}
			while (dungdexoa->prev != dungdexoa)
			{
				customer *tmp = head;
				while (tmp->next != head)
				{
					if (tmp->name == dungdexoa->name && tmp->energy == dungdexoa->energy)
					{
						cout << dungdexoa->name << "-" << dungdexoa->energy;
						tmp->prev->next = tmp->next;
						tmp->next->prev = tmp->prev;
					}
					tmp = tmp->next;
				}
				dungdexoa = dungdexoa->prev;
			}
			while (orderhead->next != NULL)
			{
				if (orderhead->energy > 0)
				{
					customer *tmp = orderhead;
					orderhead = orderhead->next;
					delete tmp;
				}
				orderhead = orderhead->next;
			}
		}

		// can dieu chinh lai curr toi vi tri vua xoa
		while (headwait != NULL && sokhach < MAXSIZE)
		{
			customer *vaoban;
			vaoban = headwait;
			RED(headwait->name, headwait->energy);
			headwait = headwait->next;
			delete vaoban;
			queuesize--;
		}
	}
	void LIGHT(int num)
	{
		customer *tmp = curr;
		if (num > 0)
		{
			for(int i=0;i<sokhach;i++){
                tmp->print();
                tmp=tmp->next;
            }
		}
		else if (num < 0)
		{

			for(int i=0;i<sokhach;i++){
                tmp->print();
                tmp=tmp->prev;
            }
		}
		else if (num == 0)
		{
			customer *tmpp = headwait;
			for(int i = 0; i < sokhach; i++){
				tmpp->print();
				tmpp = tmpp->next;
			}
		}
		cout << "light " << num << endl;
	}
};
