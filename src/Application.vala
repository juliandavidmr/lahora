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

public class ApplicationW : Window {

	Label label_date;
	private bool modeTimer = false;
	MainLoop loop = new MainLoop();
	MainLoop loopTimer = new MainLoop();
	bool pause = false;

	struct TimerStruct {
		int hour;
		int minutes;
		int seconds;
		int miliseconds;

		TimerStruct(int hour, int minutes, int seconds, int miliseconds) {
			this.hour = hour;
			this.minutes = minutes;
			this.seconds = seconds;
			this.miliseconds = miliseconds;
		}

		public bool isEmpty() {
			return miliseconds == 0 && seconds == 0 && minutes == 0 && hour == 0;
		}
	}

	TimerStruct tempo;

	public void setLabelText(string text = "") {
		if (tempo.isEmpty()) {
			if (text.length == 0) {
				DateTime dt = new DateTime.now_local();
				label_date.set_text("<span font='22'><b>" + dt.format ("%X") + "</b></span>");
			} else {
				label_date.set_text("<span font='22'><b>" + text + "</b></span>");
			}
		} else {
			label_date.set_text("<span font='22'><b>%d:%d:%d <small>%s</small></b></span>".printf(
				tempo.hour,
				tempo.minutes,
				tempo.seconds,
				alwaysThreeDigits(tempo.miliseconds)
			));
		}
		label_date.set_use_markup (true);
	}

	public void startTimeLocal() {
		var time = new TimeoutSource(1000);
		setLabelText();
		time.set_callback(() => {
			stdout.printf("Time!\n");

			if (!modeTimer) setLabelText();

			return !modeTimer;
		});
		time.attach(loop.get_context());
	}

	public string alwaysThreeDigits(int num) {
		if (num >= 100) {
			return "%d".printf(num);
		} else if (num >= 10) {
			return "0%d".printf(num);
		}
		return "00%d".printf(num);
	}

	public void startTimer() {
		var timer = new TimeoutSource(1);

		timer.set_callback(() => {
			if (++tempo.miliseconds == 1000) {
				tempo.miliseconds = 0;
				if(++tempo.seconds == 60) {
					tempo.seconds = 0;
					if(++tempo.minutes == 60) {
						tempo.minutes = 0;
						tempo.hour++;
					}
				}
			}

			setLabelText("");

			return !pause;
		});
		timer.attach(loopTimer.get_context());
		pause = false;
	}

	public void stopTimer() {
		pause = true;
		loopTimer.quit();
	}

	public ApplicationW () {
		get_style_context ().add_class (Gtk.STYLE_CLASS_FLAT);
        set_keep_below (true);
        stick ();

		// Prepare Gtk.Window:
		this.window_position = WindowPosition.CENTER;
		this.destroy.connect (Gtk.main_quit);
		this.set_default_size (300, 30);
		this.set_border_width(8);

		// add headerbar with button
		Gtk.HeaderBar headerbar = new Gtk.HeaderBar();
        headerbar.show_close_button = true;
        headerbar.title = "Lahora";
        this.set_titlebar(headerbar);

		// Button headerbar:
  		Button button = new Button.with_label ("About");
        button.clicked.connect ( () => {
			// show about dialog on click
			string[] authors = { " juliandavidmr <https://github.com/juliandavidmr>", null };
			string[] documenters = { "juliandavidmr", null };

			Gtk.show_about_dialog (this,
			                           "program-name", ("Lahora"),
			                           "copyright", ("Copyright \xc2\xa9 2018 juliandavidmr"),
			                           "authors", authors,
			                           "documenters", documenters,
			                           "website", "https://github.com/juliandavidmr",
			                           "website-label", ("Github"),
			                           null);
		});
        // add button to headerbar
        headerbar.pack_end(button);

 		Box box = new Box (Gtk.Orientation.VERTICAL, 15);
 		box.set_homogeneous(false);
 		this.add(box);

		// The Label:
		this.label_date = new Gtk.Label("");
		label_date.set_use_markup (true);
		box.add (this.label_date);

		// The thread:
		startTimeLocal();

		// Box bottom
		Box boxBottom = new Box(Gtk.Orientation.HORIZONTAL, 2);
		boxBottom.set_homogeneous(true);
		box.add(boxBottom);

		// Button play
		Gtk.Button play = new Gtk.Button.with_mnemonic("Play");
		play.clicked.connect(() => {
			if (play.label == "Pause") {
				play.label = "Play";
				stopTimer();
			} else { // Play
				play.label = "Pause";
				startTimer();
			}
		});
		boxBottom.add(play);

		// Button reset
		Gtk.Button reset = new Gtk.Button.with_mnemonic("Reset");
		reset.clicked.connect(() => {
			tempo = TimerStruct(0, 0, 0, 0);
			setLabelText("00:00:00 <small>000</small>");
		});
		boxBottom.add(reset);

		// CheckButton
		CheckButton timerModeCheck = new CheckButton.with_label ("Timer");
		timerModeCheck.toggled.connect (() => {
			// Emitted when the button has been clicked:
			if (timerModeCheck.active) {
				modeTimer = true;
				loop.quit();
				setLabelText("00:00:00 <small>000</small>");

				reset.set_sensitive(true);
				play.set_sensitive(true);
			} else {
				modeTimer = false;
				startTimeLocal();

				reset.set_sensitive(false); // to gray-out
				play.set_sensitive(false); // to gray-out
			}
		});
		headerbar.add (timerModeCheck);

		reset.set_sensitive(false); // to gray-out
		play.set_sensitive(false); // to gray-out
	}
}
