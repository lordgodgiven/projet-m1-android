package univ_fcomte.gtasks;

import univ_fcomte.tasks.Modele;
import android.app.Application;

public class MonApplication extends Application{

	private Modele modele;
	private GestionnaireTaches gt;
	private String rechercheCourante;
	
	public MonApplication() {
		modele=new Modele(this);
		rechercheCourante = "";
	}

	public String getRechercheCourante() {
		return rechercheCourante;
	}

	public void setRechercheCourante(String rechercheCourante) {
		this.rechercheCourante = rechercheCourante;
	}

	public Modele getModele() {
		return modele;
	}
	
	public void setModele(Modele modele) {
		this.modele = modele;
	}

	public GestionnaireTaches getGt() {
		return gt;
	}

	public void setGt(GestionnaireTaches gt) {
		this.gt = gt;
	}
	
}
