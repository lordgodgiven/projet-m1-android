package univ_fcomte.synchronisation;

import java.util.ArrayList;
import java.util.List;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONException;

import android.util.Log;
import android.widget.Toast;
import univ_fcomte.gtasks.GestionnaireTaches;
import univ_fcomte.gtasks.R;
import univ_fcomte.synchronisation.Synchronisation.ApiException;
import univ_fcomte.tasks.Modele;

public class ThreadSynchronisation extends Thread {

	private Synchronisation sw;
	private Modele modele;
	private GestionnaireTaches gt;
	private int modeSynchronisation;
	
	public static final int ECRASEMENT_SERVEUR = 0;
	public static final int ECRASEMENT_MOBILE = 1;
	public static final int COMBINER_SERVEUR_MOBILE = 2;
	public String reponseServeur;
	
	public ThreadSynchronisation(Modele modele, GestionnaireTaches gt, Synchronisation sw){
		this.gt = gt;
		this.sw = sw;
		this.modele = modele;
		this.modeSynchronisation = -1;
		this.reponseServeur = "";
	}
	
	public void run(){

		gt.runOnUiThread(new Runnable() {	
			@Override
			public void run() {
				gt.setProgressBarIndeterminateVisibility(true);
			}
		});
		
		switch (modeSynchronisation) {
			case ECRASEMENT_SERVEUR:
				ecraserServeur();
				break;
			case ECRASEMENT_MOBILE:
				ecraserMobile();
				break;
			case COMBINER_SERVEUR_MOBILE:
				combinerServeurMobile();
				break;
			default:
				return;	
		}
		
		gt.runOnUiThread(new Runnable() {	
			@Override
			public void run() {
				if(reponseServeur.equals(""))
					Toast.makeText(gt.getApplicationContext(), gt.getResources().getString(R.string.erreur_pas_connexion), 4000).show();
				gt.setProgressBarIndeterminateVisibility(false);
			}
		});
	}

	public void selectionModeSynchronisation(int mode){
		modeSynchronisation = mode;
	}
	
	public void ecraserMobile(){
		
		List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(2);  
		nameValuePairs.add(new BasicNameValuePair("identifiant", "guillaume"));  
		nameValuePairs.add(new BasicNameValuePair("mdPasse", sw.md5("android")));
		nameValuePairs.add(new BasicNameValuePair("objet", "importer"));
		
        try {
        	reponseServeur = sw.GetHTML(nameValuePairs);
		} catch (ApiException e1) {
			e1.printStackTrace();
		}
		
		Log.i("reponse", "code : " + reponseServeur);

		if(!reponseServeur.equals("")) {
			
			modele.reinitialiserModele();
			JsonParser json = new JsonParser(modele);
			try {
				json.parse(reponseServeur);
				Log.i("pas erreur", "code");
			} catch (JSONException e) {
				e.printStackTrace();
			}
			modele.getBdd().reinitialiserBDD(modele.getListeTags(), modele.getListeTaches(), json.getListeAPourTag(), json.getListeAPourFils());
			
			gt.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					Log.i("update", "mise a jour liste, nb tache : " + modele.getListeTaches().size());
					gt.updateList();
				}
			});
			
		}

	}
	
	public void ecraserServeur(){
		
		List<NameValuePair> nvp = new ArrayList<NameValuePair>(2);  
		nvp.add(new BasicNameValuePair("identifiant", "guillaume"));  
		nvp.add(new BasicNameValuePair("mdPasse", sw.md5("android")));
		nvp.add(new BasicNameValuePair("objet", "exporter"));
		nvp.add(new BasicNameValuePair("json", new EnvoyerJson(modele).genererJson().toString()));

		try {
			reponseServeur = sw.GetHTML(nvp);
			Log.i("reponse",reponseServeur);
		} catch (ApiException e) {
			e.printStackTrace();
		}
		
	}
	
	public void combinerServeurMobile(){
		
	}
	
}