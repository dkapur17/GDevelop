import { roundPosition } from '../Utils/GridHelpers';

export default class InstancesMover {
  constructor({ instanceMeasurer, options }) {
    this.instanceMeasurer = instanceMeasurer;
    this.options = options;
    this.instancePositions = {};
    this.totalDeltaX = 0;
    this.totalDeltaY = 0;
  }

  setOptions(options) {
    this.options = options;
  }

  _roundXPosition(x, noGridSnap) {
    if (!this.options.snap || !this.options.grid || noGridSnap)
      return Math.round(x);

    return roundPosition(x, this.options.gridWidth, this.options.gridOffsetX);
  }

  _roundYPosition(y, noGridSnap) {
    if (!this.options.snap || !this.options.grid || noGridSnap)
      return Math.round(y);

    return roundPosition(y, this.options.gridHeight, this.options.gridOffsetY);
  }

  _getMoveDeltaX(followAxis) {
    if (followAxis && Math.abs(this.totalDeltaX) < Math.abs(this.totalDeltaY))
      return 0;

    return this.totalDeltaX;
  }

  _getMoveDeltaY(followAxis) {
    if (followAxis && Math.abs(this.totalDeltaY) < Math.abs(this.totalDeltaX))
      return 0;

    return this.totalDeltaY;
  }

  moveBy(instances, deltaX, deltaY, followAxis, noGridSnap) {
    this.totalDeltaX += deltaX;
    this.totalDeltaY += deltaY;

    for (var i = 0; i < instances.length; i++) {
      const selectedInstance = instances[i];

      let initialPosition = this.instancePositions[selectedInstance.ptr];
      if (!initialPosition) {
        initialPosition = this.instancePositions[selectedInstance.ptr] = {
          x: selectedInstance.getX(),
          y: selectedInstance.getY(),
        };
      }

      selectedInstance.setX(
        this._roundXPosition(
          initialPosition.x + this._getMoveDeltaX(followAxis),
          noGridSnap
        )
      );
      selectedInstance.setY(
        this._roundYPosition(
          initialPosition.y + this._getMoveDeltaY(followAxis),
          noGridSnap
        )
      );
    }
  }

  endMove() {
    this.instancePositions = {};
    this.totalDeltaX = 0;
    this.totalDeltaY = 0;
  }
}
