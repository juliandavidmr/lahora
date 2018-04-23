/* main.vala
 *
 * Copyright (C) 2018 juliandavidmr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

using Gtk;

public class Application : Gtk.Window {

	Label label_date;

	public void setDateLabel() {
		DateTime dt = new DateTime.now_utc();
		label_date.set_text("<span font='22'><b>" + dt.format ("%X") + "</b></span>");
		label_date.set_use_markup (true);
		label_date.set_line_wrap (true);
		Thread.usleep (1000);
	}

	public Application () {
		// Prepare Gtk.Window:

		this.title = "Clock";
		this.window_position = WindowPosition.CENTER;
		this.destroy.connect (Gtk.main_quit);
		this.set_default_size (300, 30);

 		Box box = new Gtk.Box (Gtk.Orientation.VERTICAL, 2);
 		this.add(box);

		// The Label:
		this.label_date = new Gtk.Label("");
		this.label_date.set_use_markup (true);
		this.label_date.set_line_wrap (true);
		box.add (this.label_date);

		// The thread
		var loop = new MainLoop();
		var time = new TimeoutSource(1000);

		setDateLabel();
		time.set_callback(() => {
			stdout.printf("Time!\n");
			setDateLabel();
			return true;
		});

		time.attach(loop.get_context());

		// Gtk.Button play = new Gtk.Button.with_mnemonic(Play);
		// box.add(play);
	}
}

int main (string[] args) {
	Gtk.init (ref args);

	if (!Thread.supported ()) {
		stderr.printf ("Cannot run without thread support.\n");
		return 1;
	}

	Application app = new Application ();
	app.show_all ();
	Gtk.main ();
	return 0;
}
