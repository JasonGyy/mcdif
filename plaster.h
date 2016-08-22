#ifndef SITE_H
#define SITE_H
#include "site.h"
#endif

#ifndef GENERATORS_H
#define GENERATORS_H
#include "generators.h"
#endif

#ifndef LIST_H
#define LIST_H
#include <list>
#endif

//http://stackoverflow.com/questions/20854068/removing-object-pointer-from-stl-list
//http://www.cplusplus.com/reference/list/list/remove_if/

class plaster {
	
	private:
	vector <site*> PL_REF_TO_SITES;			//przechowuje wszystkie sity w plastrze
	vector < list < site* > > PL_SITES_TYP;
	
	string PL_NAME;
	unsigned int PL_TYPES,PL_DIRECTION,PL_INDEX;
	double PL_P0,PL_P1,PL_AVG_COUNT;		//P - pozycja poczatkowa i koncowa plastra |....| size bin
	vector <long> PL_EQ_FLUX;
	vector <long> PL_NET_FLUX;
	vector <long> PL_PROB_ADD;
	vector <long> PL_PROB_DEL;
	vector<double> PL_ATOMS;
	vector<double> PL_AVG_PARS;	//p0,p1,A,B,V,flux_A,...,eq_fluxA,..., counter;
	unsigned long PL_JUMPS;
	public:
	
	plaster(int i, int atoms_type, int direction, int id, double x0 , double x1 , string name = "rezerv");	

	void	cumulate();
	void	call_avg(vector<double>& results);
	void	set_atoms_list(vector <site *> &kontener, int typ);
	void	set_atoms_list(list <site *> &kontener, int typ);
	void	init_calc(int FLAG=0);
	bool	check(unsigned int typ_min, unsigned int typ_max, int delta);
	void	swap(plaster source, int FLAG);
	int		get_direction(){return PL_DIRECTION;};
	int		get_st(){return PL_P0;};
	int		get_end(){return PL_P1;};
	int		get_index(){return PL_INDEX;};
	string		get_name(){return PL_NAME;};


	void	push_back( site* item ){
				PL_REF_TO_SITES.push_back(item);
			};
		
	unsigned int	size(){
		return PL_REF_TO_SITES.size();
	};
	
	unsigned int	size(int typ){
		return PL_SITES_TYP[typ].size();
	};
	
	unsigned int	get_size_types(){
		return PL_SITES_TYP.size();
	};
	
	site* get_site(long pozition){
		return PL_REF_TO_SITES[pozition];
	}
	
	site* get_site(int typ,int nr){
		list<site*>::iterator it= PL_SITES_TYP[typ].begin();
		advance(it, nr);
		return *it;
	};
	
	void	delete_site(int typ, long numer){
		list<site*>::iterator item = PL_SITES_TYP[typ].begin();
		advance(item, numer);
		PL_SITES_TYP[typ].erase(item);
		eq_flux_delta(typ,0);
		
	};
	
	void	add_site(int typ, site* new_site){
		PL_SITES_TYP[typ].push_back(new_site);
		eq_flux_delta(typ,1);
	};
	
	void jump_occured(){
		PL_JUMPS++;
	};

	void eq_flux_delta(unsigned int typ, int flaga){
		//flaga =0 -> site remved; flaga=1 -> site created in plaster
		if(typ>=PL_EQ_FLUX.size()){cout<<"ERROR in plaster::eq_flux: "<<typ<<endl;exit(1);}
		if(flaga==1){
			PL_EQ_FLUX[typ]++;
		}else if(flaga==0){
			PL_EQ_FLUX[typ]--;		
		}
		else{cout<<"ERROR in plaster::eq_flux"<<endl;exit(1);}
	};

	void flux_net_delta(unsigned int typ, int flaga){
		//flaga =0 -> site remved; flaga=1 -> site created in plaster
		if(typ>=PL_NET_FLUX.size()){cout<<"ERROR in plaster::net_flux: "<<typ<<endl;exit(1);}
		if(flaga==1){
			PL_NET_FLUX[typ]++;
		}else if(flaga==0){
			PL_NET_FLUX[typ]--;		
		}
		else{cout<<"ERROR in plaster::net_flux"<<endl;exit(1);}
	};
	
	void prob_update(unsigned int typ, int flaga){
		//flaga =0 -> site remved; flaga=1 -> site created in plaster
		if(flaga==1){
			if(typ>=PL_PROB_ADD.size()){cout<<"ERROR in plaster::flux: "<<typ<<endl;exit(1);}
			PL_PROB_ADD[typ]++;
		}else if(flaga==0){
			if(typ>=PL_PROB_DEL.size()){cout<<"ERROR in plaster::flux: "<<typ<<endl;exit(1);}
			PL_PROB_DEL[typ]++;		
		}
		else{cout<<"ERROR in plaster::flux"<<endl;exit(1);}
	};

	long eq_flux_get(unsigned int typ){
		if(typ>=PL_EQ_FLUX.size()){cout<<"ERROR in plaster::eq_flux: "<<typ<<endl;exit(1);}
		return PL_EQ_FLUX[typ];
	};

	long net_flux_get(unsigned int typ){
		if(typ>=PL_NET_FLUX.size()){cout<<"ERROR in plaster::eq_flux: "<<typ<<endl;exit(1);}
		return PL_NET_FLUX[typ];
	};
	
	long flux_net_get(unsigned int typ){
		if(typ>=PL_NET_FLUX.size()){cout<<"ERROR in plaster::net_flux: "<<typ<<endl;exit(1);}
		return PL_NET_FLUX[typ];
	};

	site* &operator[](unsigned int i){
		if( i > PL_REF_TO_SITES.size() ){
			cout << "Index out of bounds" <<endl; 
            // return first element.
            return PL_REF_TO_SITES[0];
		}
		return PL_REF_TO_SITES[i];
	};
 		

	double get_stech(){
		double stech = static_cast<double> (PL_ATOMS[1])/(static_cast<double> (PL_ATOMS[2]) + static_cast<double> (PL_ATOMS[1]));
	
		return stech;
	};

	double get_vac(){
		long int size = PL_REF_TO_SITES.size();	
		double vac = static_cast<double> (PL_ATOMS[0])/static_cast<double> (size);
		return vac;
	};


};
