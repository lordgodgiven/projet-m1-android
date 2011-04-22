package univ_fcomte.gtasks;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;

public class ErreurDialog {

	public ErreurDialog(int titre, int message, Context context) {

		AlertDialog.Builder builder = new AlertDialog.Builder(context);
		builder.setTitle(titre);
		builder.setMessage(message);
		builder.setCancelable(false);
		builder.setPositiveButton(R.string.ok, new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int id) {}
		});
		AlertDialog alert = builder.create();
		alert.show();

	}
	
}
