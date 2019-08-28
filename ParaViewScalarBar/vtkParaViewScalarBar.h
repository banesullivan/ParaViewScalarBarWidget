#ifndef vtkParaViewScalarBar_h
#define vtkParaViewScalarBar_h

#include <vtkNew.h>
#include <vtkObject.h>
#include <vtkWeakPointer.h>

class vtkAbstractWidget;
class vtkContext2DScalarBarActor;
class vtkDiscretizableColorTransferFunction;
class vtkPVScalarBarRepresentation;
class vtkRenderer;
class vtkRenderWindowInteractor;
class vtkScalarBarWidget;
class vtkWidgetRepresentation;

class vtkParaViewScalarBar : public vtkObject
{
public:
  static vtkParaViewScalarBar* New();
  vtkTypeMacro(vtkParaViewScalarBar, vtkObject)
  void PrintSelf(ostream& os, vtkIndent indent) override;

  //@{
  /**
   * Get/Set whether the widget is enabled.
   */
  void SetEnabled(bool);
  vtkGetMacro(Enabled, bool)
  vtkBooleanMacro(Enabled, bool)
  //@}

  void SetTitle(const std::string& title);
  void SetComponentTitle(const std::string& title);
  const std::string& GetTitle();
  const std::string& GetComponentTitle();

  // vtkContext2DScalarBarActor works only with a vtkDiscretizableColorTransferFunction
  void SetLookupTable(vtkDiscretizableColorTransferFunction *lut);

  /**
   * ...
   */
  void SetRenderer(vtkRenderer*);
  void SetInteractor(vtkRenderWindowInteractor* interactor);

protected:
  vtkParaViewScalarBar();
  ~vtkParaViewScalarBar() override;

  /**
   * Updates 'Enabled' on this->Widget.
   */
  void UpdateEnabled();

  /**
   * Callback whenever the representation is modified. We call UpdateEnabled()
   * to ensure that the widget is not left enabled when the representation is
   * hidden.
   */
  void OnRepresentationModified();

  void ExecuteEvent(vtkObject*, unsigned long, void*);
  /**
   * Synchronizes Position2 length definition of the scalar bar widget with the
   * ScalarBarLength property.
   */
  void ScalarBarWidgetPosition2ToScalarBarLength();
  void ScalarBarLengthToScalarBarWidgetPosition2();

protected:
  bool Enabled;

  vtkNew<vtkContext2DScalarBarActor> ScalarBarActor;
  vtkNew<vtkPVScalarBarRepresentation> Representation;
  vtkNew<vtkScalarBarWidget> Widget;

  // instead of using a vtkView
  vtkWeakPointer<vtkRenderer> Renderer;
  vtkWeakPointer<vtkRenderWindowInteractor> Interactor;

private:
  vtkParaViewScalarBar(const vtkParaViewScalarBar&) = delete;
  void operator=(const vtkParaViewScalarBar&) = delete;

private:
  unsigned long RepresentationObserverTag;
};

#endif
