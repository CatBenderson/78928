import { Component } from '@angular/core';

@Component({
  selector: 'app-menu',
  templateUrl: './menu.component.html',
  styleUrls: ['./menu.component.css']
})
export class MenuComponent {
  opciones:Array<String>;

  constructor(){
    this.opciones=['inicio','acerca','contacto']
  }
}
